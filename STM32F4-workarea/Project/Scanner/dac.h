#ifndef _DAC_H
#define _DAC_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "misc.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void setDAC(char channel, uint16_t value);

#endif
