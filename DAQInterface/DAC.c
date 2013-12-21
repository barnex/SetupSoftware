#include "DAC.h"

int initDAC(int SYNCpin, int address, DAC_struct *DAC)
{
    memset(&(DAC->buffer), 0, sizeof(dac_tx_struct));
    DAC->buffer.address = address;
    
    DAC->SYNCpin = SYNCpin;
    INP_GPIO( SYNCpin );
    OUT_GPIO( SYNCpin );
    GPIO_SET = 1 << SYNCpin;

    DAC->fd = open("/dev/spidev0.1", O_RDWR);\
    assert( DAC->fd > 0 );
    return 0;
}

int freeDAC(DAC_struct *DAC)
{
    return close(DAC->fd);
}

int setDAC(DAC_struct *DAC, int channel, double value)
{
    uint16_t dacvalue = (uint16_t) ((value/2.5)*65536.0);
    DAC->buffer.valueMSB = (char) (dacvalue >> 16);
    DAC->buffer.valueLSB = (char) (dacvalue & 0xffff);

    DAC->buffer.powerDown   = 0;
    DAC->buffer.channel     = channel;
    DAC->buffer.zero        = 0;
    DAC->buffer.command     = 1;

    uint64_t dummy = 0;
    struct spi_ioc_transfer tr = {
        .tx_buf         = (unsigned long) &(DAC->buffer),
        .rx_buf         = &dummy,
        .len            = 3,
        .delay_usecs	= 0,
        .bits_per_word  = 8,
        .speed_hz	    = 2000000
    };

    return ioctl(DAC->fd, SPI_IOC_MESSAGE(1), &tr);
}
