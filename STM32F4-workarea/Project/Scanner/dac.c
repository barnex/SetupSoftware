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
    dac.value      = ((value >> 8) & 0x00ff) | ((value << 8) & 0xff00);

    uint8_t *buffer = (uint8_t *)(&dac);
    for(int i = 0; i < 4; i++ )
    {
        SPI2->DR = buffer[i];
        while( !(SPI2->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    }

    // Bring PB11 back high
    GPIOB->BSRRL |= GPIO_Pin_11;
}

void setDACS(uint16_t *values)
{
    for(int i = 0; i < 4; i++)
    {
	setDAC(i, values[i]);
	volatile uint32_t j = 0xff;
	while(j--);
    }
    /*
    dac_tx_struct dac;

    dac.powerDown = 0;
    dac.zero      = 0;
    dac.address   = 0;
    dac.command   = 0; // Load value and do not update DAC
    for(int i = 0; i < 4 ; i++ )
    {
        // Bring PB11 low
        GPIOB->BSRRH |= GPIO_Pin_11;
            
        dac.channel   = i;
        dac.value     = values[i];
        if( i == 3 )
        {
            dac.command = 2; // Load value and update all the DACs
        }

        uint8_t *buffer = (uint8_t *)(&dac);
        for(int j = 0; j < 3; j++ )
        {
            SPI2->DR = buffer[j];
            while( !(SPI2->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
        }

        // Bring PB11 back high
        GPIOB->BSRRL |= GPIO_Pin_11;
	uint8_t tmp = 0xff;
	while(tmp--);
    }
    */
}
