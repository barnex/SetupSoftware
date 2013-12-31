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

#define STATE_ABORT             (uint8_t) 0
#define STATE_ACTIVE            (uint8_t) 1
#define STATE_IDLE              (uint8_t) 2
#define STATE_START             (uint8_t) 3

#define OUT_CMD_FIRSTPIXEL      (uint8_t) 1
#define OUT_CMD_LASTPIXEL       (uint8_t) 2
#define OUT_CMD_SCANNING        (uint8_t) 3
#define OUT_CMD_DAC             (uint8_t) 4
#define OUT_CMD_CHAN            (uint8_t) 5
#define OUT_CMD_START           (uint8_t) 6

#define IN_CMD_ABORT            (uint8_t) 0
#define IN_CMD_GOTO             (uint8_t) 1
#define IN_CMD_START            (uint8_t) 2
#define IN_CMD_SET_DACX         (uint8_t) 3
#define IN_CMD_SET_DACY         (uint8_t) 4
#define IN_CMD_SET_DACZ         (uint8_t) 5
#define IN_CMD_SET_DACAUX       (uint8_t) 6
#define IN_CMD_GET_DAC          (uint8_t) 7
#define IN_CMD_GET_CHAN         (uint8_t) 8
#define IN_CMD_SET_START        (uint8_t) 9
#define IN_CMD_SET_PIXELS       (uint8_t) 10
#define IN_CMD_SET_TSETTLE      (uint8_t) 11
#define IN_CMD_SET_IINC         (uint8_t) 12
#define IN_CMD_SET_JINC         (uint8_t) 13

#define USART_WDT_ACTIVE        (uint8_t) 1
#define USART_WDT_INACTIVE      (uint8_t) 2

#define USART_STATE_CMD         (uint8_t) 0
#define USART_STATE_SIZE        (uint8_t) 1
#define USART_STATE_PAYLOAD     (uint8_t) 2

volatile int32_t    position[4];
volatile int32_t    start[4];
volatile int32_t    i_inc[4];
volatile int32_t    j_inc[4];
volatile int32_t    scan_i;
volatile int32_t    scan_j;
volatile int32_t    pixels;
volatile uint32_t   t_settle;
volatile uint8_t    state;
volatile uint16_t   DACBuffer[4];
volatile int16_t    ADCBuffer[8];
volatile uint16_t   USARTBuffer[16];
volatile uint8_t    uart_wdt_state;
volatile uint8_t    uart_state;

struct commandstructure
{
    unsigned char cmd   :8;
    unsigned char size  :8;
} command_out, command_in;

void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}

void USART_puts(USART_TypeDef* USARTx, volatile char *s){

    while(*s){
        // wait until data register is empty
        while( !(USARTx->SR & 0x00000040) );
        USART_SendData(USARTx, *s);
        *s++;
    }
}

void shipDataOut(uint16_t * buffer, uint32_t n)
{
    // First ship out the command byte
    while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET );
    USART_SendData(USART1, command_out.cmd); 
    while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET );
    USART_SendData(USART1, command_out.size); 
    for(int i = 0; i < n; i++ )
    {
        while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET );
        USART_SendData(USART1, buffer[i] && 0x00ff );
        while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET );
        USART_SendData(USART1, buffer[i] >> 8);
    }

}

inline void halt()
{
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); // Disable throwing interrupts
    TIM_Cmd(TIM2, DISABLE);                     // Disable timer completely
    TIM_SetCounter(TIM2, (uint32_t) 0);         // Reset counter register
    GPIO_ResetBits(GPIOD, 0xF000);              // Dim the LED's
    state = STATE_IDLE;                               // Switch to idle state
}

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

inline void parseInput()
{
    if( command_in.cmd == IN_CMD_ABORT )
    {
        state = STATE_ABORT;
    }
    else if( command_in.cmd == IN_CMD_START )
    {
        halt();
        state = STATE_START;
    }
}

int main()
{
	init_LEDs();
    init_Timer(5000);
    
	init_USART1(460800);
    init_ADC();
    init_DAC();
    state = STATE_IDLE;
	USART_puts(USART1, "Init complete\r\n");
    

	while(1)
	{
        if( state == STATE_ABORT)
        {
            halt();
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
            if( state == STATE_ACTIVE )
            {
                init_Timer(t_settle);
            }
            shipDataOut((uint16_t *)ADCBuffer, (uint32_t) 8);
            state = STATE_IDLE;

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
            init_Timer(t_settle);
            state = STATE_IDLE;
        }
	}
	return 0;
}

void TIM2_IRQHandler(void)
{
    if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        TIM_Cmd(TIM2, DISABLE);
        while( state == STATE_ACTIVE );
        
        if( state == STATE_IDLE )
        {
            state = STATE_ACTIVE;
        }
    }
}

void TIM3_IRQHandler(void)
{
    if( TIM_GetITStatus(TIM3, TIM_IT_UPDATE) != RESET )
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        TIM_Cmd(TM3, DISABLE);
        usart_wdt_state = USART_WDT_INACTIVE;
    }

}

void USART1_IRQHandler(void){
    // check if the USART1 receive interrupt flag was set
    if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
	    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
        usart_wdt_state = USART_WDT_ACTIVE;
        usart_state = USART_STATE_CMD;
        memset(USARTBuffer, 0, sizeof(uint16_t)*16);
        uint32_t i = 0;

        while( usart_wdt_state == USART_WDT_ACTIVE )
        {
            if( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET )
            {
                if( usart_state == USART_STATE_CMD )
                {
                    command_in.cmd = USART1->DR;
                    usart_state = USART_STATE_SIZE;
                }
                else if( usart_state == USART_STATE_SIZE )
                {
                    command_in.size = USART1->DR;
                    usart_state = USART_STATE_PAYLOAD;
                }
                else if( usart_state == USART_STATE_PAYLOAD )
                {
                    if( i % 2 == 0)
                    {
                        USARTBuffer[i/2] = USART1->DR;
                    }
                    else
                    {
                        USARTBuffer[i/2] = USART1->DR << 8;
                    }
                    i++;
                    if( i >= command_in.size )
                    {
                        usart_wdt_state = USART_WDT_INACTIVE;
                    }
                }
            }
        }

        parseInput();
	    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    }
}
