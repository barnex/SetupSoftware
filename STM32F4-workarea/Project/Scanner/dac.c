#include "dac.h"

struct dac_tx_struct
{
    // Most significant byte
    unsigned int powerDown  :1;
    unsigned int channel    :2;
    unsigned int zero       :1;
    unsigned int command    :2; 
    unsigned int address    :2;
       
    unsigned int value      :16;
} dac_tx_struct;

void setDAC(char channel, uint16_t value)
{
    // Bring PB11 low
    GPIOB->BSRRH |= GPIO_Pin_11;

    dac_tx_struct.powerDown = 0;
    dac_tx_struct.zero      = 0;
    dac_tx_struct.address   = 0;
    dac_tx_struct.channel   = channel;
    dac_tx_struct.command   = 1; // Load value and update DAC
    dac_tx_stuct.value      = value;

    uint8_t *buffer = (uint8_t *)(&dac_tx_struct);
    for(int i = 0; i < 4; i++ )
    {
        SPI2->DR = buffer[i];
        while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    }

    // Bring PB11 back high
    GPIOB->BSRRH |= GPIO_Pin_11;


}
