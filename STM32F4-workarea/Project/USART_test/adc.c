#include "adc.h"

void readChannel(char channel, int16_t * value)
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
    //Drive CONVST high and back low
    GPIOA->BSRRL |= GPIO_Pin_1;
    nCount = 0x00ff;
    while(nCount--);
    GPIOA->BSRRH |= GPIO_Pin_1;

    while ( !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) );

    // During this second I/O operation the results from the previous conversion are saved
    SPI1->DR = *buffer;
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete
    uint8_t tmp = SPI1->DR;
    SPI1->DR = 0x00; // Transmit dummy byte
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete

    uint16_t tmp2 = (tmp << 8) | SPI1->DR;
    *value = (int16_t) tmp2;

}

void readChannels(int16_t *value)
{
    GPIOA->BSRRH |= GPIO_Pin_1; // Bring CONVST low
    uint16_t tmp = 0xff;
    while(tmp--);
    GPIOA->BSRRL |= GPIO_Pin_2; // CONVST high again
    tmp = 0xff;
    while(tmp--);

    while ( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) );

    GPIOA->BSRRH |= GPIO_Pin_3; // CS low
    for(uint32_t i = 0; i < 4; i++)
    {
	SPI1->DR = 0x00; // Transmit dummy byte
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete
	value[i] = SPI1->DR << 8;
	SPI1->DR = 0x00; // Transmit dummy byte
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete
	value[i] |= SPI1->DR;	
    }
    GPIOA->BSRRL |= GPIO_Pin_3; // CS high
}
