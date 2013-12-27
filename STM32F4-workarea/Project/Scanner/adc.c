#include "adc.h"

void readChannel(char channel, uint16_t * value)
{
    //Drive CONVST (PA1) low
    GPIOA->BSRRH |= GPIO_Pin_1;

    adc_tx_struct adc;
    adc.sleep   = 0;
    adc.nap     = 0;
    adc.gain    = 0;
    adc.uni     = 0;
    adc.sgl     = 1;
    adc.select  = channel / 2;
    adc.odd     = channel % 2;

    uint8_t * buffer = (uint8_t *)(&adc);
    // During this first I/O operation the results from the previous conversion are discarded!
    SPI1->DR = *buffer;
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    SPI1->DR = 0x00; // Transmit dummy byte
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
   
    // Wait for ~5us 
    int nCount = 0x00ff;
    while(nCount--);
    //Drive CONVST high
    GPIOA->BSRRL |= GPIO_Pin_1;

    while ( !(GPIOA->IDR & 0x0003) ); // Wait while PA3 (~BUSY) is low

    // During this second I/O operation the results from the previous conversion are saved
    SPI1->DR = *buffer;
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete
    uint8_t tmp = SPI1->DR;
    SPI1->DR = 0x00; // Transmit dummy byte
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete

    *value = (tmp << 8) | SPI1->DR;

}
