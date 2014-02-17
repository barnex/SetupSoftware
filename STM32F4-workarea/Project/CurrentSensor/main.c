#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "misc.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define REQUEST_VALUE 251

void initADC(void);
void initUSART(uint32_t baudrate);
void USART_puts(volatile char *s);
volatile uint8_t requestValue;

int main(void)
{
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 ); 
    initADC();
    initUSART(115200);
    int index = 0;
    uint16_t ADCBuffer[16];
    memset(ADCBuffer, 0, sizeof(uint16_t));
    uint16_t avgReading = 0;

    requestValue = 0;

    while(1)
    {
	while(  ADC_GetFlagStatus( ADC1, ADC_FLAG_EOC) == RESET );
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	ADCBuffer[index] = ADC_GetConversionValue(ADC1);
	index++;
	if(index >= 16)
	    index = 0;

	avgReading = 0;
	for(int i = 0; i < 16; i++ )
	{
	    avgReading += ADCBuffer[i];
	}

	if( requestValue )
	{
	    USART_SendData(USART3, avgReading >> 8);
	    while( !( USART_GetFlagStatus(USART3,USART_FLAG_TXE) ) );
	    USART_SendData(USART3, avgReading & 0x00ff);
	    while( !( USART_GetFlagStatus(USART3,USART_FLAG_TXE) ) );
	    requestValue = 0;
	}
    }

    return 0;
}

void initADC(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIOInit;
    GPIOInit.GPIO_Pin = GPIO_Pin_1;
    GPIOInit.GPIO_Mode = GPIO_Mode_AN;
    GPIOInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIOInit);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_InitTypeDef ADCInit;
    ADC_StructInit( &ADCInit );
    ADCInit.ADC_Resolution = ADC_Resolution_12b;
    ADCInit.ADC_ScanConvMode = DISABLE;
    ADCInit.ADC_ContinuousConvMode = ENABLE;
    ADCInit.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
    ADCInit.ADC_DataAlign = ADC_DataAlign_Right;
    ADCInit.ADC_NbrOfConversion = 1;

    ADC_CommonInitTypeDef ADCCommonInit;
    ADC_CommonStructInit( &ADCCommonInit );
    ADCCommonInit.ADC_Mode = ADC_Mode_Independent;
    ADCCommonInit.ADC_Prescaler = ADC_Prescaler_Div8;

    ADC_Init(ADC1, &ADCInit);
    ADC_CommonInit( &ADCCommonInit );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_480Cycles);
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);

}

void initUSART(uint32_t baudrate){

    GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
    USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization
    NVIC_InitTypeDef NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; // Pins 6 (TX) and 7 (RX) are used
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;		// the pins are configured as alternate function so the USART peripheral has access to them
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	// this defines the IO speed and has nothing to do with the baudrate!
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;		// this defines the output type as push pull mode (as opposed to open drain)
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		// this activates the pullup resistors on the IO pins
    GPIO_Init(GPIOD, &GPIO_InitStruct);			// now all the values are passed to the GPIO_Init() function which sets the GPIO registers

    /* The RX and TX pins are now connected to their AF
 *   * so that the USART1 can take over control of the
 *	 * pins
 *	     */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3); //
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

    /* Now the USART_InitStruct is used to define the
 *   * properties of USART1
 *	 */
    USART_InitStruct.USART_BaudRate = baudrate;		    // the baudrate is set to the value we passed into this init function
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;// we want the data frame size to be 8 bits (standard)
    USART_InitStruct.USART_StopBits = USART_StopBits_1;	    // we want 1 stop bit (standard)
    USART_InitStruct.USART_Parity = USART_Parity_No;	    // we don't want a parity bit (standard)
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // we want to enable the transmitter and the receiver
    USART_Init(USART3, &USART_InitStruct);		    // again all the properties are passed to the USART_Init function which takes care of all the bit setting


    /* Here the USART1 receive interrupt is enabled
 *   * and the interrupt controller is configured
 *	 * to jump to the USART1_IRQHandler() function
 *	     * if the USART1 receive interrupt occurs
 *		 */
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	     // we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	     // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	     // the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure);			     // the properties are passed to the NVIC_Init function which takes care of the low level stuff

    // finally this enables the complete USART1 peripheral
    USART_Cmd(USART3, ENABLE);
}

void USART3_IRQHandler(void)
{
    if( USART_GetITStatus( USART3, USART_IT_RXNE ) )
    {
	uint8_t usartInput = USART3->DR;
	if( usartInput == REQUEST_VALUE )
	{
	    requestValue = 1;
	}
    }
}
