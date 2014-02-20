#ifndef _MONA_H
#define _MONA_H

#include "portaudio.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <unistd.h>

#define SAMPLE_RATE (48000)
#include "ringbuffer.h"


void pipe_catcher(int signo);
typedef struct{
	int discard;
	// A pointer to the captured data
	ringBuffer *in;
	// A pointer to the data that can be copied to the output
	float *out;
	// Toggle flag to indicate new data is available
	char toggleFlag;
	// A mutex to disable access if the callback function is called
	pthread_mutex_t lock;
} PACallbackData;

typedef struct{
	// A pointer to where to captured audio is stored
	PACallbackData *PACallbackArgs;
	// A pointer to where the concatenated audio is stored
	ringBuffer *input;
	// The size of the final FFT in number of audio buffers
	int FFTsize;
	// A mutex lock to disable killing the dataCopyThread until all data has been
	//shipped to the client
	pthread_mutex_t threadlock;	
} CopyThreadData;

typedef struct
{
    fftw_real **data;
    int length;
    int width;
    int sockfd;
} FFTThreadData;

#endif
