#ifndef _DAC_H
#define _DAC_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "misc.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    // Most significant byte
    unsigned int powerDown  :1;
    unsigned int channel    :2;
    unsigned int zero       :1;
    unsigned int command    :2; 
    unsigned int address    :2;
       
    unsigned int value      :16;
} dac_tx_struct;


void setDAC(char channel, uint16_t value);

#endif
