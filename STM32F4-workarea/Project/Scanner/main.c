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
volatile char received_string[MAX_STRLEN];

volatile char state;

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

int main()
{
	init_LEDs();
	init_USART1(460800);
    init_ADC();
    init_DAC();
    state = 0;
	//RCC_ClocksTypeDef myClocks;
	//RCC_GetClocksFreq(&myClocks);
	USART_puts(USART1, "Init complete\r\n");

	while(1)
	{
        if( state == 0 )
        {
            GPIOD->BSRRL = 0xF000;
            uint16_t buffer[8];
            readChannels( buffer );
            char outstr[64];
            memset(outstr, 0, 64);
            sprintf(outstr, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n",
                buffer[0], buffer[1], buffer[2], buffer[3],
                buffer[4], buffer[5], buffer[6], buffer[7]);
            USART_puts(USART1, outstr);
            state = 1;
            GPIOD->BSRRH = 0xF000;
        }
        else if( state == 1 )
        {
            GPIOD->BSRRL = 0x1000;
            GPIOD->BSRRH = 0x8000;
            Delay(1000000L);
            GPIOD->BSRRL = 0x2000;
            GPIOD->BSRRH = 0x1000;
            Delay(1000000L);
            GPIOD->BSRRL = 0x4000;
            GPIOD->BSRRH = 0x2000;
            Delay(1000000L);
            GPIOD->BSRRL = 0x8000;
            GPIOD->BSRRH = 0x4000;
            Delay(1000000L);
        }
        else
        {
            GPIOD->BSRRH = 0xF000;
        }
	}
	return 0;

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

void TIM2_IRQHandler(void)
{

}
