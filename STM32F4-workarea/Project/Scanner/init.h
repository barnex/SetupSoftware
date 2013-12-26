#ifndef _MYINIT_H
#define _MYINIT_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include <stdio.h>
#include <stdint.h>

void init_USART1(uint32_t baudrate);
void init_SPI1(void);
void init_SPI2(void);
void init_LEDs();


#endif

