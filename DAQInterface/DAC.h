#ifndef _DAC_H
#define _DAC_H

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
    unsigned int powerDown  :1;
    unsigned int channel    :2;
    unsigned int zero       :1;
    unsigned int command    :2; 
    unsigned int address    :2;
       
    unsigned int valueMSB   :8;
    unsigned int valueLSB   :8;
} dac_tx_struct;

typedef struct
{
    int fd;
    int SYNCpin;
    dac_tx_struct buffer;
} DAC_struct;

// Initializes the LTC1859 and the necessary structs, returns 0 on success
int initDAC(int SYNCpin, int address, DAC_struct *DAC);

// Frees a ADC struct
int freeDAC(DAC_struct *DAC);

// Sets the voltage (value in [V]) of DAC channel (0..3).
int setDAC(DAC_struct *DAC, int channel, double value);

#endif
