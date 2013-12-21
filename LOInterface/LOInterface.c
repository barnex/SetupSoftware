#include "LOInterface.h"

static int writeLO(LOInterface *LO)
{
   int ret = 0;
    ret = ioctl(LO->fd, SPI_IOC_MESSAGE(1), LO->tr);
    return ret; 
}

int initLO(LOInterface *LO, const char *device)
{
    LO->tr		= malloc(sizeof(struct  spi_ioc_transfer));

    LO->RX_BUF.padding	= 0x00;
    LO->RX_BUF.payload	= 0x00;
    LO->TX_BUF.rw	= 0;
    LO->TX_BUF.address	= 0x00;
    LO->TX_BUF.payload	= 0x00;
    LO->tr->tx_buf	= (unsigned long) &(LO->TX_BUF);
    LO->tr->rx_buf	= (unsigned long) &(LO->RX_BUF);
    LO->tr->len		= 2;
    LO->tr->delay_usecs	= 0;
    LO->tr->bits_per_word   = 8;
    LO->tr->speed_hz	= 2000000;

    LO->device		= device;
    LO->fd		= open(LO->device, O_RDWR);

    if(LO->fd > 0)
    {
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x08;
	writeLO(LO);
	printf("Default entry in register 0x08 is 0x%2x\n", LO->RX_BUF.payload);
	LO->TX_BUF.address = 0x0B;
	writeLO(LO);
	printf("Revno. %d, partno. %d\n", (LO->RX_BUF.payload >> 5), (LO->RX_BUF.payload & 0b11111) );

	// Set 10MHz reference, >2V Input 
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x08;
	writeLO(LO);
	uint8_t retval = LO->RX_BUF.payload;
	retval = (retval & 0b111) | (0b11 << 5) | (0b10 << 3);
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = retval;
	writeLO(LO);

	// Disable REF out buffer and disable mute
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x02;
	writeLO(LO);
	retval = LO->RX_BUF.payload;
	retval = (retval & 0b11110101);
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = retval;
	writeLO(LO);

	// Set the reference divider for 1MHz PFD
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.address = 0x04;
	LO->TX_BUF.payload = 10;
	writeLO(LO);

	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x03;
	writeLO(LO);
	retval = LO->RX_BUF.payload;
	retval = (retval & 0xfc);
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = retval;
	writeLO(LO);

	// Maximum current on charge pump
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x09;
	writeLO(LO);
	retval = LO->RX_BUF.payload;
	retval = (retval & 0xf0) | 11;
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = retval;
	writeLO(LO);

	// B divider set for 1MHz PFD
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x03;
	writeLO(LO);
	retval = LO->RX_BUF.payload;
	retval = (retval & 0x0f);
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = retval;
	writeLO(LO);

	// Enable ALC only during calibration
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x07;
	writeLO(LO);
	retval = LO->RX_BUF.payload;
	retval = (retval & 0x2f);
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = retval;
	writeLO(LO);
	

    }
    /* Return if opening a port to the LO was succesfull */
    return LO->fd;
}

int freeLO(LOInterface *LO)
{
    close(LO->fd);
    free(LO->tr);
    return 0;
}

int setFrequency(float f, LOInterface *LO)
{
    int freq = (int)(f);
    printf("f = %d\n", freq);
    if( (freq > 3840 && freq < 5790) || (freq < 2895 && freq > 640) )
    {
	uint8_t O_DIV = 0;
	uint16_t N_DIV;
	/* Check in which frequency range the required frequency falls */
	if( freq > 3840 )
	{
	    O_DIV = 1;
	}
	else if( freq > 1920 )
	{
	    O_DIV = 2;
	}
	else if( freq > 1280 )
	{
	    O_DIV = 3;
	}
	else if( freq > 960 )
	{
	    O_DIV = 4;
	}
	else if( freq > 768 )
	{
	    O_DIV = 5;
	}
	else if( freq > 640 )
	{
	    O_DIV = 6;
	}
	/* From the O-divider, calculate the N-divider */
	N_DIV = O_DIV * freq;

	/* Send the value of the N-divider to the PLL */
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.address = 0x05;
	/* Highest byte (RPi uses little endian */
	LO->TX_BUF.payload = (N_DIV >> 8);
	writeLO(LO);
	LO->TX_BUF.address = 0x06;
	/* Lowest byte */
	LO->TX_BUF.payload = (uint8_t) (0x00ff & N_DIV);
	writeLO(LO);

	/* Send the O-divider and power value, but keep the other values in the same register (ergo read first) */	
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x08;
	writeLO(LO);
	uint8_t returnval = (LO->RX_BUF.payload & 0b11100000 ) | 0b00011000 | O_DIV;
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = returnval;
	writeLO(LO);

	/* Free the charge pump */
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.address = 0x0A;
	LO->TX_BUF.payload = 0xC0;
	writeLO(LO);

	/* Calibrate?! */
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x07;
	writeLO(LO);
	returnval = (LO->RX_BUF.payload & 0b11111101) | 0b10;
	LO->TX_BUF.rw = 0b0;
	LO->TX_BUF.payload = returnval;
	writeLO(LO);

	/* Now check for a lock */
	LO->TX_BUF.rw = 0b1;
	LO->TX_BUF.address = 0x00;
	writeLO(LO);
	uint8_t flags = LO->RX_BUF.payload & 0x1F;
	LO->TX_BUF.address = 0x01;
	writeLO(LO);
	uint8_t vals = LO->RX_BUF.payload & 0x1F;
	uint8_t stat = ( vals & flags );
	if( stat != 0 )
	{
	    fprintf(stderr, "! ERROR: Could not lock the PLL\n");
	    return -2;
	}
	else
	{
	    return 0;
	}
    }
    else
    {
	fprintf(stderr, "! ERROR: Requested frequency %e is out of range of the PLL\n", f);
	return -1;
    }
}

int setOutput(int enable, LOInterface *LO)
{
    LO->TX_BUF.rw = 0b1;
    LO->TX_BUF.address = 0x02;
    writeLO(LO);
    uint8_t returnval = 0x00;
    if(enable > 0)
    {
        returnval = (LO->RX_BUF.payload & 0b11111101);
    }
    else
    {
        returnval = (LO->RX_BUF.payload & 0b11111101) | 0b10;
    }
    LO->TX_BUF.rw = 0b0;
    LO->TX_BUF.payload = returnval;
    writeLO(LO);

    return 0;
}
