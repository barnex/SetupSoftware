#ifndef _LOINTERFACE_H
#define _LOINTERFACE_H

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

typedef struct 
{
    unsigned int rw	    :1;
    unsigned int address    :7;
    unsigned int payload    :8;
} tx_buffer;

typedef struct
{
    unsigned int padding    :8;
    unsigned int payload    :8;
} rx_buffer;

typedef struct
{
    int			fd;
    tx_buffer		TX_BUF;
    rx_buffer		RX_BUF;
    struct spi_ioc_transfer *tr;
    const char	*device;
} LOInterface;

/*
 * This function should allocate the required space and set default parameters.
 * On the hardware side it should soft-reset the LO and init to specific default
 * values (e.g. output off, ...)
 */
int initLO(LOInterface *LO, const char *device);

/*
 * Call this function when all finished with the device. It will leave the device
 * running as is.
 */
int freeLO(LOInterface *LO);

/*
 * Sets the frequency of the LO, specified in Hertz
 */
int setFrequency(float f, LOInterface *LO);

/*
 * Sets the output power
 */
int setPower(int level, LOInterface *LO);

/*
 * Enables or disables output
 */
int setOutput(int enable, LOInterface *LO);

#endif
