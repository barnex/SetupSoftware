#include "ADC.h"

int initADC(int CONVSTpin, int BUSYpin, ADC_struct *ADC)
{
    memset(&(ADC->buffer), 0, sizeof(adc_tx_struct));
    
    ADC->CONVSTpin = CONVSTpin;
    INP_GPIO( CONVSTpin );
    OUT_GPIO( CONVSTpin );
    GPIO_CLR = 1 << CONVSTpin;

    ADC->fd = open("/dev/spidev0.0", O_RDWR);
    assert( ADC->fd > 0 );

    int mode = SPI_CS_HIGH;
    int ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    assert( ret != -1 );
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    assert( ret  != -1 );
    return 0;
}

int freeADC( ADC_struct *ADC )
{
    close( ADC->fd );
}

int readADC(ADC_struct *ADC, int channel, double * value)
{
    if( channel % 2 == 0 )
    {
        ADC->odd = 0;
    }
    else
    {
        ADC->odd = 1;
    }
    ADC->odd = (channel % 2);
    ADC->select = ( channel / 2 );

            

    case( channel )
    {
        switch 0:   ADC->odd = 0;
                    ADC->select = 0;
                    break;
        switch 1:   ADC->odd = 1;
                    ADC->select = 1;
                    break;
       switch 2:    ADC->odd = 0;
                    ADC->select = 1;
                    break;
       switch 3:    ADC->odd = 1;

    }

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
