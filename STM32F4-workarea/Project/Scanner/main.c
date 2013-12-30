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

#define MAX_STRLEN 64

#define ABORT   (uint32_t) 0
#define ACTIVE  (uint32_t) 1
#define IDLE    (uint32_t) 2
#define START   (uint32_t) 3

#define FIRSTPIXEL  (uint8_t) 1
#define LASTPIXEL   (uint8_t) 2
#define SCANNING    (uint8_t) 3

volatile char received_string[MAX_STRLEN];


volatile int32_t    position[4];
volatile int32_t    start[4];
volatile int32_t    i_inc[4];
volatile int32_t    j_inc[4];
volatile int32_t    scan_i;
volatile int32_t    scan_j;
volatile int32_t    pixels;
volatile uint32_t   t_settle;
volatile uint32_t   state;
volatile uint16_t   DACBuffer[4];
volatile int16_t    ADCBuffer[8];

union cmdstrct
{
    uint16_t bytes;
    struct commandstructure
    {
        unsigned char cmd   :8;
        unsigned char size  :8;
    } bits;
} command;

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
    USART_SendData(USART1, command.bytes); 
    for(int i = 0; i < n; i++ )
    {
        while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET );
        USART_SendData(USART1, buffer[i]);
    }

}

inline void halt()
{
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); // Disable throwing interrupts
    TIM_Cmd(TIM2, DISABLE);                     // Disable timer completely
    TIM_SetCounter(TIM2, (uint32_t) 0);         // Reset counter register
    GPIO_ResetBits(GPIOD, 0xF000);              // Dim the LED's
    state = IDLE;                               // Switch to idle state
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

int main()
{
	init_LEDs();
    init_Timer(5000);
    while(1);
    /*
	init_USART1(460800);
    init_ADC();
    init_DAC();
    state = 0;
	//RCC_ClocksTypeDef myClocks;
	//RCC_GetClocksFreq(&myClocks);
	USART_puts(USART1, "Init complete\r\n");
    */

	while(1)
	{
        if( state == ABORT)
        {
            halt();
        }
        else if(state == ACTIVE)
        {
            command.bits.cmd = SCANNING;
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
                    command.bits.cmd = LASTPIXEL;
                    halt();
                }
            getPosition();
            setDACS((uint16_t *) DACBuffer);
            if( state == ACTIVE )
            {
                init_Timer(t_settle);
            }
            shipDataOut((uint16_t *)ADCBuffer, (uint32_t) 8);
            state = IDLE;

        }
        else if(state == IDLE)
        {
           // NOP
        }
        else if(state == START)
        {
            command.bits.cmd = FIRSTPIXEL;
            command.bits.size = (uint8_t) 8;
            // Set the start position
            scan_i = 0;
            scan_j = 0;
            getPosition();
            setDACS((uint16_t *) DACBuffer);
            // Start the timer to allow the stage to settle
            init_Timer(t_settle);
            state = IDLE;
        }
	}
	return 0;

}

void TIM2_IRQHandler(void)
{
    if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        TIM_Cmd(TIM2, DISABLE);
        while( state == ACTIVE );
        
        if( state == IDLE )
        {
            state = ACTIVE;
        }
    }
}

void USART1_IRQHandler(void){

    // check if the USART1 receive interrupt flag was set
    if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

        
        char t = USART1->DR; // the character from the USART1 data register is saved in t

        /* check if the received character is not the LF character (used to determine end of string)
         * or the if the maximum string length has been been reached
         */
        if( t == 0x61 )
        {
            state = 1;
            USART_puts(USART1, "Disabling...\r\n");
        }
        else if( t == 0x62 )
        {
           state = 0;
           USART_puts(USART1, "Toggled measurement...\r\n");
        }
        else if( t == 0x63 )
        {
            state = 3;
        }
    }
}
