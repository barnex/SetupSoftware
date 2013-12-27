#ifndef _ADC_H
#define _ADC_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "misc.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    // Most significant byte
    unsigned int sleep      :1;
    unsigned int nap        :1;
    unsigned int gain       :1;
    unsigned int uni        :1; 
    unsigned int select     :2;
    unsigned int odd        :1;
    unsigned int sgl        :1;
} adc_tx_struct;
 
void readChannel(char channel, uint16_t * value);
void readChannels(uint16_t *values);
#endif
