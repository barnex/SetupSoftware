#ifndef _MYINIT_H
#define _MYINIT_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include <stdio.h>
#include <stdint.h>

/*
 * PD8 = TX
 * PD9 = RX
 */
void init_USART(uint32_t baudrate);

/*
 * This function initializes SPI1-transceiver as follows:
 * PA5 = SCK (idle high, sample 2nd edge)
 * PA6 = MISO
 * PA1 = CONVST (out)
 * PA2 = RESET (out)
 * PA3 = ~CS (out)
 * PA4 = BUSY
 * PE7 = HIGH (required to disable LIS302DL)
 */
void init_ADC(void);

/*
 * PB11 ~SYNC
 * PB13 SCLK
 * PB14 MISO
 * PB15 MOSI
*/
void init_DAC(void);


void init_LEDs();

void init_Timer(uint32_t t_settle);

void init_USART_WDT();
#endif

