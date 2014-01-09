#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "init.h"
#include "adc.h"
#include "dac.h"
#include "mydefs.h"

volatile int32_t    position[4];    // Current position, though signed int, strictly positive and smaller than 0xFFFF
volatile int32_t    start[4];	    // The state position (see comment above)
volatile int32_t    i_inc[4];	    // The smaller increase vector (")
volatile int32_t    j_inc[4];	    // The larger increase vector (")
volatile int32_t    scan_i;	    // The current small index of the scan (<pixels)
volatile int32_t    scan_j;	    // The current large index of the scan (<pixels)
volatile int32_t    pixels;	    // The number of pixels in the image
volatile uint32_t   t_settle;	    // The number of milliseconds to let the DAC/stage settle
volatile uint8_t    state;	    // The current state of the main state machine
volatile uint16_t   DACBuffer[4];   // The value the is copied to the DAC
volatile int16_t    ADCBuffer[8];   // The value that is read from the ADC
volatile uint16_t   USARTBuffer[16];	// The values that have been read/written from/to the USART
volatile uint8_t    usart_state;    // The current state of the USART state machine

/*
 * Before shipping data out, set command_out.size and command_out.cmd to make
 * clear to the user what he is about to receive. On the receiving hand, parseInput
 * uses these to check what the user is requesting/writing.
 */
struct commandstructure
{
    unsigned char cmd   :8;	// One of the 256 possible commands
    unsigned char size  :8;	// Up to 256 bytes can be sent, and it's specified right here!
} command_out, command_in;

void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}

/*
 * Use this function only for debugging and outputting strings.
 */
void USART_puts(USART_TypeDef* USARTx, volatile char *s){

    while(*s){
        // wait until data register is empty
        while( !(USARTx->SR & 0x00000040) );
        USART_SendData(USARTx, *s);
        *s++;
    }
}

/*
 * Function ships n uint16_t words out through the serial port
 */
void shipDataOut(uint16_t * buffer, uint32_t n)
{
    // First ship out the command byte
    while( USART_GetFlagStatus(USART3, USART_FLAG_TXE) != SET );
    USART_SendData(USART3, command_out.cmd); 
    while( USART_GetFlagStatus(USART3, USART_FLAG_TXE) != SET );
    USART_SendData(USART3, command_out.size); 
    for(int i = 0; i < n; i++ )
    {
        while( USART_GetFlagStatus(USART3, USART_FLAG_TXE) != SET );
        USART_SendData(USART3, buffer[i] && 0x00ff );
        while( USART_GetFlagStatus(USART3, USART_FLAG_TXE) != SET );
        USART_SendData(USART3, buffer[i] >> 8);
    }

}

/*
 * Halts Timer2 and associated interrupt, which disables waking from STATE_IDLE
 */
inline void halt()
{
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); // Disable throwing interrupts
    TIM_Cmd(TIM2, DISABLE);                     // Disable timer completely
    TIM_SetCounter(TIM2, (uint32_t) 0);         // Reset counter register
    GPIO_ResetBits(GPIOD, 0xF000);              // Dim the LED's
}

/*
 * This inline function calculates the current position from the indices of
 * the pixels. No check on bounds!
 */
inline void getPosition()
{
    position[0] = start[0] + scan_i*i_inc[0] + scan_j*pixels*j_inc[0];
    DACBuffer[0] = (uint16_t) position[0];
    position[1] = start[1] + scan_i*i_inc[1] + scan_j*pixels*j_inc[1];
    DACBuffer[1] = (uint16_t) position[1];
    position[2] = start[2] + scan_i*i_inc[2] + scan_j*pixels*j_inc[2];
    DACBuffer[2] = (uint16_t) position[2];
    position[3] = start[3] + scan_i*i_inc[3] + scan_j*pixels*j_inc[3];
    DACBuffer[3] = (uint16_t) position[3];
}

/*
 * There can be some discussion on the work divsion between this function
 * and the main state machine loop. Input parsing happens in an ISR (USART3_IRQn)
 * and should be as short as possible. Therefore it can only change the machine
 * state and copy values from USARTBuffer and to the USART (e.g. GET_DAC), 
 * as other interrupts might otherwise interfere. All the rest is executed 
 * by the main state machine below.
 */
inline void parseInput()
{
    /*
     *  We move the state machine into the ABORT state
     */
    if( command_in.cmd == IN_CMD_ABORT )
    {
        state = STATE_ABORT;
    }
    /*
     *  We move the state machine into the starting state
     */
    else if( command_in.cmd == IN_CMD_START )
    {
        halt();
        state = STATE_START;
    }
    /*
     *  We abort the current scan (if in progress) and
     *  copy the values from the USART into the position
     *  and move into the GOTO state (and later update the real position)
     */
    else if (command_in.cmd == IN_CMD_GOTO && command_in.size >= 8 )
    {
	halt();
	position[0] = (int32_t) USARTBuffer[0];
	position[1] = (int32_t) USARTBuffer[1];
	position[2] = (int32_t) USARTBuffer[2];
	position[3] = (int32_t) USARTBuffer[3];
	state = STATE_GOTO;
    }
    /*
     *  When a simple parameter read is requested, the state machine
     *  does not get altered.
     */
    else if ( command_in.cmd == IN_CMD_GET_DAC )
    {
	command_out.cmd = OUT_CMD_DAC;  // Let the user know we are sending out DAC values
	command_out.size    = 8;	    // Though confusing, 4 uint16_t will be transmitted,
					    // which corresponds with 8 bytes
	USARTBuffer[0] = (uint16_t)  position[0];
	USARTBuffer[1] = (uint16_t)  position[1];
	USARTBuffer[2] = (uint16_t)  position[2];
	USARTBuffer[3] = (uint16_t)  position[3];
	shipDataOut((uint16_t *)USARTBuffer, 4);
    }
    /*
     * We simply move the state machine into single shot measurement state
     */ 
    else if ( command_in.cmd == IN_CMD_GET_CHAN )
    {
	halt();
	state = STATE_SINGLE_MEAS;
    }
    /*
     *	We abort the current state and update the starting position
     */
    else if ( command_in.cmd == IN_CMD_SET_START && command_in.size >= 8 )
    {
	halt();
	state = STATE_IDLE;
	start[0] = (int32_t) USARTBuffer[0];
	start[1] = (int32_t) USARTBuffer[1];
	start[2] = (int32_t) USARTBuffer[2];
	start[3] = (int32_t) USARTBuffer[3];
    }
    /*
     * Abort and update settle time
     */
    else if ( command_in.cmd == IN_CMD_SET_TSETTLE && command_in.size >= 2)
    {
	halt();
	state = STATE_IDLE;
	t_settle = (uint32_t) USARTBuffer[0];
    }
    /*
     * Abort and update the number of pixels
     */
    else if ( command_in.cmd == IN_CMD_SET_PIXELS && command_in.size >= 2)
    {
	halt();
	state = STATE_IDLE;
	pixels = (int32_t) USARTBuffer[0];
    }
    /*
     * Abort and update the small increase vector
     */
    else if ( command_in.cmd == IN_CMD_SET_IINC && command_in.size >= 8)
    {
	halt();
	state = STATE_IDLE;
	i_inc[0] = (int32_t) USARTBuffer[0];
	i_inc[1] = (int32_t) USARTBuffer[1];
	i_inc[2] = (int32_t) USARTBuffer[2];
	i_inc[3] = (int32_t) USARTBuffer[3];
    }
    /*
     * Abort and update the large increase vector
     */
    else if ( command_in.cmd == IN_CMD_SET_JINC && command_in.size >= 8 )
    {
	halt();
	state = STATE_IDLE;
	j_inc[0] = (int32_t) USARTBuffer[0];
	j_inc[1] = (int32_t) USARTBuffer[1];
	j_inc[2] = (int32_t) USARTBuffer[2];
	j_inc[3] = (int32_t) USARTBuffer[3];
    }

}


int main()
{
    /* 
     * This is important and you should understand the following:
     * PriorityGroup_4 ALLOWS FOR ONLY PREEMPTIVE INTERRUPTS AND NO SUB-GROUPINGS
     * You should always set the NVIC_PriorityGroup.
     */  
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 ); 

    init_LEDs();
    //init_Timer(5000);
  
    // Always set the USART watchdog before the USART self 
    init_USART_WDT();
    init_USART(115200);
    init_ADC();
    init_DAC();
    USART_puts(USART3, "Init complete\r\n");

    state = STATE_IDLE;
    // A loop that will run until the end of times (or when you switch of the controller)
    while(1)
    {
	/*
	 * The following is the state machine for the scanning procedure. It knows the following states:
	 * STATE_IDLE: nothing is done in this state. You can not depart from this state, only external
	 *	interrupt can leave from this state to another state.
	 * STATE_START:	This is the initial state when the scanning is started. It will initialize the
	 *	scanning parameters and move the state machine into a dynamical machine.
	 * STATE_ACTIVE: This state firstly measures the current inputs and then calculates and
	 *	moves to the next pixel. It inializes Timer2 to wait a specific time before a next
	 *	measurement. Then it moves the state machine into the STATE_IDLE state, from which
	 *	it will awake using Timer2 interrupt.
	 * STATE_ABORT:	This state is called externally (USART). When the machine is moved in this state,
	 *	current scanning is aborted (all interrupts/timers disabled) and the machine is moved into
	 *	the STATE_IDLE state. It cannot awake until moved externally.
	 * STATE_SINGLE_MEAS: In this state, one measurement is made and returned to the user. Afterwards
	 *	it returns to the STATE_IDLE.
	 * STATE_GOTO: Adjusts the position to the user's request and goes to the STATE_IDLE
	 */
        if( state == STATE_ABORT)
        {
            halt();
	    state = STATE_IDLE;
        }
        else if(state == STATE_ACTIVE)
        {
            command_out.cmd = OUT_CMD_SCANNING;
            GPIO_SetBits(GPIOD, 0xF000);
            readChannels((int16_t *)ADCBuffer);
            scan_i++;
            if( scan_i >= pixels )
            {
                scan_i = 0;
                scan_j++;
                if( scan_j >= pixels )
                {
                    scan_j = 0;
                    command_out.cmd = OUT_CMD_LASTPIXEL;
                    halt();
                }
            }
            getPosition();
            setDACS((uint16_t *) DACBuffer);
	    // If we are still in the active state (and user has not called for ABORT)...
            if( state == STATE_ACTIVE )
            {
                init_Timer(t_settle);
		state = STATE_IDLE;
            }
            shipDataOut((uint16_t *)ADCBuffer, (uint32_t) 8);
        }
        else if(state == STATE_IDLE)
        {
           // NOP
        }
        else if(state == STATE_START)
        {
            command_out.cmd = OUT_CMD_FIRSTPIXEL;
            command_out.size = (uint8_t) 8;
            // Set the start position
            scan_i = 0;
            scan_j = 0;
            getPosition();
            setDACS((uint16_t *) DACBuffer);
            // Start the timer to allow the stage to settle
            if( state == STATE_START )
	    {
		init_Timer(t_settle);
		state = STATE_IDLE;
	    }
	}
	else if( state == STATE_GOTO )
	{
	    // Copy and cast the data into the buffer
	    DACBuffer[0] = (uint16_t) position[0];
	    DACBuffer[1] = (uint16_t) position[1]; 
	    DACBuffer[2] = (uint16_t) position[2]; 
	    DACBuffer[3] = (uint16_t) position[3]; 
	    // Update the DAC values
            setDACS((uint16_t *) DACBuffer);
	    // Check if the state was not modified externally
	    if( state == STATE_GOTO )
	    {
		state = STATE_IDLE;
	    }

	}
	else if( state == STATE_SINGLE_MEAS )
	{
	    // Read data from the ADC
            readChannels((int16_t *)ADCBuffer);
	    // And write it into the USART
            shipDataOut((uint16_t *)ADCBuffer, (uint32_t) 8);
	    // Check if the state was not modified externally
	    if( state == STATE_SINGLE_MEAS )
	    {
		state = STATE_IDLE;
	    }

	}
    }
    return 0;
}

// ISR for the the settling time timer
void TIM2_IRQHandler(void)
{
    if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
	// If the timer overflowed... clear the interrupt bit
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	// Disable the timer
        TIM_Cmd(TIM2, DISABLE);

	// Check that we are not in an active state, else wait for it to finish
        //while( state == STATE_ACTIVE );
    
	// If we were waiting (and not ABORT) then we proceed to the next pixel    
        if( state == STATE_IDLE )
        {
            state = STATE_ACTIVE;
        }
    }
}


// Function that gets called everytime something gets received to reset the USART WDT
void reset_USART_WDT(void)
{
	// Disable interrupts for a second
        TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
	// Reset the timer
        TIM_SetCounter(TIM3, (uint32_t) 0);
	// Enable the timer (should it have been disabled)
        TIM_Cmd(TIM3, ENABLE);
	// Clear the interrupt bit and enable interrupt (ALWAYS clear bit before enabling!)
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

// TIM3 is the USART watchdog (highest interrupt priority)
void TIM3_IRQHandler(void)
{
    // If an update interrupt was thrown...
    if( TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET )
    {
	// Disable the WDT for the moment
        TIM_Cmd(TIM3, DISABLE);
	// Switch on the LED to signal timeout
	GPIOD->BSRRL |= GPIO_Pin_15;
	// Clear the interrupt bit
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// Disable the interrupt
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
	// Switch USART state to timeout
        usart_state = USART_STATE_TIMEOUT;
    }

}

/*
 * This ISR is called when data has been received from the USART. Using
 * a state machine, it tries to parse data input. However if it should not
 * receive enough data or the connection hangs, it will time out through a
 * watchdog timer. Data is pumped through as follows:
 *	* first byte: command, IN_CMD_...
 *	* second byte: the number of bytes to be received
 *	* following bytes: the payload data, these bytes will be grouped into 
 *	    uint16_t's. LSB comes first.
 */
void USART3_IRQHandler(void){
    // check if the USART3 receive interrupt flag was set
    if( USART_GetITStatus(USART3, USART_IT_RXNE) )
    {
	GPIOD->BSRRH |= GPIO_Pin_15 | GPIO_Pin_13;
	
	// Disables interrupts, we will be "reading by blocking", not "interrupt reading"
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);

	// Init the USART Watchdog and state machine
        usart_state = USART_STATE_CMD;

	// Clear the memory
        memset((void *)USARTBuffer, 0, sizeof(uint16_t)*16);
        uint32_t i = 0;

	// Reset the USART watchdog timer
	reset_USART_WDT();

	/*
	 * The USART state machine consists of the following states:
	 * USART_STATE_CMD: The interrupt is called for the first time, the first byte is sent
	 *	through and this holds the command. State moves to USART_STATE_SIZE.
	 * USART_STATE_SIZE: Now the second byte is received, this holds the number of bytes
	 *	that will be sent through. These bytes are grouped into uint16_t!! The state
	 *	moves to USART_STATE_PAYLOAD.
	 * USART_STATE_PAYLOAD: The previously specified number of bytes are now read and
	 *	converted into uint16_t values in USARTBuffer[0..15]. When the specified
	 *	number of bytes have been read the state changes to USART_STATE_FINISHED
	 * USART_STATE_FINISHED: Now the loop is broken and we progress to parse the input.
	 *	This state will finish the ISR and reenable the USART interrupt.
	 * USART_STATE_TIMEOUT: The USART watchdog timer has timed out the connection. The
	 *	loop and ISR will break here without trying to parse the input.
	 */

	// Keep trying to read whilst the USART is active (i.e. not finished and not timed out)
        while( usart_state != USART_STATE_TIMEOUT && usart_state != USART_STATE_FINISHED )
        {
	    // If something was received...
            if( USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET )
            {
		// Reset the watchdog
		reset_USART_WDT();
		// Depending on the state of the USART state machine, copy the byte to the correct place
                if( usart_state == USART_STATE_CMD )
                {
                    command_in.cmd = USART3->DR;
                    usart_state = USART_STATE_SIZE;
                }
                else if( usart_state == USART_STATE_SIZE )
                {
                    command_in.size = USART3->DR;
                    usart_state = USART_STATE_PAYLOAD;
                }
                else if( usart_state == USART_STATE_PAYLOAD )
                {
                    if( i % 2 == 0)
                    {
			// Read the LSByte firstly
                        USARTBuffer[i/2] = USART3->DR;
                    }
                    else
                    {
			// Now concatenate with the MSByte
                        USARTBuffer[i/2] |= USART3->DR << 8;
                    }
                    i++;
                }
            }
	    
	    // Check if the correct number of bytes have been received
            if( usart_state == USART_STATE_PAYLOAD )
            {
                if( i >= command_in.size )
                {
		    // If so, stop receiving
                    usart_state = USART_STATE_FINISHED;
                }
            }
        }

	// If the USART didn't time out
	if( usart_state != USART_STATE_TIMEOUT )
	{
	    // Parse the input and disable the watchdog timer
	    parseInput();
            TIM_Cmd(TIM3, DISABLE);
	    GPIOD->BSRRL |= GPIO_Pin_13;
	}
    }
    // After finished the ISR, enable it again.
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}
