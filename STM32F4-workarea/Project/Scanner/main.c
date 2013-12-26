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
	init_USART1(115200);
    state = 0;
	//RCC_ClocksTypeDef myClocks;
	//RCC_GetClocksFreq(&myClocks);
	USART_puts(USART1, "Init complete\r\n");

	while(1)
	{
        switch(state)
        {
            case 0: GPIOD->BSRRL = 0xF000;
		            Delay(1000000L);
		            GPIOD->BSRRH = 0xF000;
                    break;
            case 1: GPIOD->BSRRL = 0x1000;
		            Delay(1000000L);
                    GPIOD->BSRRH = 0x1000;
                    GPIOD->BSRRL = 0x2000;
		            Delay(1000000L);
                    GPIOD->BSRRH = 0x2000;
                    GPIOD->BSRRL = 0x4000;
		            Delay(1000000L);
                    GPIOD->BSRRH = 0x4000;
                    GPIOD->BSRRL = 0x8000;
		            Delay(1000000L);
                    GPIOD->BSRRH = 0x8000;
                    break;
            default: break;
        }
		Delay(1000000L);
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
           USART_puts(USART1, "Enabling...\r\n");
        }
        else if( t == 0x63 )
        {
            state = 3;
        }
    }
}
