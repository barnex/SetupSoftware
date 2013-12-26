#include "dac.h"

void setDAC(char channel, uint16_t value)
{
    // Bring PB11 low
    GPIOB->BSRRH |= GPIO_Pin_11;

    dac_tx_struct dac;

    dac.powerDown = 0;
    dac.zero      = 0;
    dac.address   = 0;
    dac.channel   = channel;
    dac.command   = 1; // Load value and update DAC
    dac.value      = value;

    uint8_t *buffer = (uint8_t *)(&dac);
    for(int i = 0; i < 4; i++ )
    {
        SPI2->DR = buffer[i];
        while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    }

    // Bring PB11 back high
    GPIOB->BSRRH |= GPIO_Pin_11;


}
