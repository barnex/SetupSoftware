#include "adc.h"


void readChannel(char channel, int16_t * value)
{
    //while ( !(GPIOA->IDR & 0x0003) ); // Wait while PA3 (~BUSY) is low
    //while( ~GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) );

    //Drive CONVST (PA1) low
    GPIOA->BSRRH |= GPIO_Pin_1;

    volatile adc_tx_struct adc;
    adc.sleep   = 0;
    adc.nap     = 0;
    adc.gain    = 0;
    adc.uni     = 0;
    adc.sgl     = 1;
    adc.select  = channel / 2;
    adc.odd     = channel % 2;

    volatile uint8_t * buffer = (uint8_t *)(&adc);
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

    //while ( !(GPIOA->IDR & 0x0003) ); // Wait while PA3 (~BUSY) is low
    uint32_t wdt = 0xfff;
    while( ~GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) && wdt-- );

    // During this second I/O operation the results from the previous conversion are saved
    SPI1->DR = *buffer;
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete
    uint8_t tmp = SPI1->DR;
    SPI1->DR = 0x00; // Transmit dummy byte
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until transmit complete

    uint16_t tmp2 = tmp | ( SPI1->DR << 8 );
    memcpy(value, &tmp2, 2);
}

void readChannels(int16_t *value)
{
    for(int i = 0; i <8; i++ )
    {
	readChannel(i, &(value[i]));
    }
}

/*
void readChannels(int16_t *value)
{
    // Initialisation for the first measurement 
    while ( !(GPIOA->IDR & 0x0003) ); // Wait while PA3 (~BUSY) is low
    //Drive CONVST (PA1) low
    GPIOA->BSRRH |= GPIO_Pin_1;
    adc_tx_struct adc;
    adc.sleep   = 0;
    adc.nap     = 0;
    adc.gain    = 0;
    adc.uni     = 0;
    adc.sgl     = 1;

    // Sample channel 0
    char channel = 0;

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
 
    //
    // Iterate over the other channels
    // whilst reading the result from the previous samplings
    // 
    while( channel < 8 )
    {
        // Increase the channel (wrap around at 8)
        channel += 1;
        adc.select  = (channel % 8) / 2;
        adc.odd     = channel % 2;

        while ( !(GPIOA->IDR & 0x0003) ); // Wait while PA3 (~BUSY) is low

        // During this second I/O operation the results from the previous conversion are saved
        SPI1->DR = *buffer;
        while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
        while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
        uint8_t tmp = SPI1->DR;
        SPI1->DR = 0x00; // Transmit dummy byte
        while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
        while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete

        uint16_t tmp2 = (tmp << 8) | SPI1->DR;
        value[channel-1] = (int16_t) tmp2;

        // Wait for ~5us 
        int nCount = 0x00ff;
        while(nCount--);
        //Drive CONVST high
        GPIOA->BSRRL |= GPIO_Pin_1;
        nCount = 0x00ff;
        while(nCount--);
        GPIOA->BSRRH |= GPIO_Pin_1; // CONVST -> low
    }
}
*/
