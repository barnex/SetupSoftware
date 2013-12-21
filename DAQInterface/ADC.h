#ifndef _ADC_H
#define _ADC_H

#include <assert.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <errno.h>
#include <string.h>

#include "GPIO.h"

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

    unsigned int padding    :8;
       
} adc_tx_struct;

typedef struct
{
    int fd;
    int CONVSTpin;
    int BUSYpin;
    adc_tx_struct buffer;
} ADC_struct;

// Initializes the DAC8564 and the necessary structs, returns 0 on success
int initADC(int CONVSTpin, int BUSYpin, ADC_struct *ADC);

// Frees a DAC struct
int freeADC(ADC_struct *ADC);

// Reads the voltage (value in [V]) of ADC channel (0..7).
int readADC(ADC_struct *ADC, int channel, double * value);

#endif
