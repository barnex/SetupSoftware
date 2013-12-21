#include "ringbuffer.h"

void initRingBuffer(ringBuffer *buff, int length, int width)
{
	buff->length = length;
	buff->width = width;
	buff->index = 0;
	buff->buffer = malloc(sizeof(float*)*buff->width);
	int i = 0;
	for( i = 0 ; i < width; i++ )
	{
		buff->buffer[i] = malloc(sizeof(float)*buff->length);
	}
}

void freeRingBuffer(ringBuffer *buff)
{
	int i = 0;
	for( i = 0 ; i < buff->width ; i++ )
	{
		free(buff->buffer[i]);
	}
	free(buff->buffer);
}

void inline deinterleave( const void *input, int lengthInput, ringBuffer *buffer )
{
    int i = 0;
    for( i = 0 ; i < lengthInput ; i++ )
    {
	int j = 0;
	for( j = 0; j < buffer->width; j++ )
	{
	    buffer->buffer[j][buffer->index] = ((float *)input)[i*buffer->width+j];
	}
	buffer->index += 1; 
	if( buffer->index >= buffer->length )
	{
	    buffer->index = 0;
	}
    }
}

void inline copy( ringBuffer *input, int startIndex, int stopIndex, ringBuffer *output )
{
    int i = startIndex;
    while( i != stopIndex )
    {
	int j = 0;
	for( j = 0; j < input->width; j++ )
	{
	    output->buffer[j][output->index] = input->buffer[j][i];
	}

	i++;
	if( i >= input->length )
	{
	    i = 0;
	}
	output->index += 1;
	if( output->index >= output->length )
	{
	    output->index = 0;
	}
    }
    
}

void printRingBuffer( ringBuffer *buffer, int stopIndex, int length )
{
    int startIndex = 0;
    if( stopIndex - length < 0 )
    {
	startIndex = buffer->length - ( stopIndex - length );
    }	
    else
    {
	startIndex = stopIndex - length;
    }
    int index = startIndex;
    while( index != stopIndex ) 
    {
	printf("%d : %f\n", index, buffer->buffer[0][index]);
	index++;
	if( index >= buffer->length )
	{
	    index = 0;
	}
    }
    
}

void inline unroll( ringBuffer *input, int startIndex, int length, fftw_real **unrolled )
{
    int index = startIndex, i = 0;
    while( i < length )
    {
	int j = 0;	
	for(j = 0 ; j < input->width; j++ )
	{
	    unrolled[j][i] = (fftw_real) input->buffer[j][index];
	}
	i++;
	index++;
	if( index > input->length )
	{
	    index = 0;
	}
    }
}

void reset( ringBuffer *buffer)
{
    buffer->index = 0;
    /*
    int i = 0 ;
    for( i = 0 ; i < buffer->width; i++ )
    {
	bzero(buffer->buffer, buffer->length*4);
    }
    */
}
