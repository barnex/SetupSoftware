#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <rfftw.h>

typedef struct{
	int length;
	int width;
	// Index = the index of the last block that was added.
	int index;
	float **buffer;
} ringBuffer;

/*
 * Initializes a ring buffer, requires:
 * - length : the size (# of elements) in each block
 * - width : the parallel number of blocks
 */
void initRingBuffer(ringBuffer *buff, int length, int width);
void freeRingBuffer(ringBuffer *buff);

/*
 * Deinterleaves data coming from the portaudio stream into
 * the output ringbuffer. The length of input needs to be equal to 
 * the length x width of the ringbuffer
 */
void inline deinterleave( const void *input, int lengthInput, ringBuffer *outputBuffer );

/*
 * Copies data from the input ring buffer (starting from startIndex and stopping
 * at stopIndex) into the output ring buffer
 */
void inline copy( ringBuffer *input, int startIndex, int stopIndex, ringBuffer *output );

/*
 * Will copy data from the input ringbuffer starting from startIndex up to (not including) startIndex + length
 * into the unrolled buffer. "unrolled" must be allocated before use!
 */
void inline unroll( ringBuffer *input, int startIndex, int length, fftw_real **unrolled );

void printRingBuffer( ringBuffer *buffer, int stopIndex, int length );

void reset( ringBuffer * buffer );

#endif
