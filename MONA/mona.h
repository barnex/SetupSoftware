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
} callbackData;

typedef struct{
	// A pointer to where to captured audio is stored
	callbackData *paCallbackData;
	// A pointer to where the concatenated audio is stored
	ringBuffer *input;
	// A pointer to where to final FFT has to be stored
	complex *result;
	// The size of the final FFT in number of audio buffers
	int fftsize;
	// The callback function that gets called if all the FFT's are finished
	void (* callback)(void *, fftw_real **fftresult, int length, int width);
	// Arguments to this function
	void *callbackArgs;
} dataCopyThreadData;

typedef struct
{
    fftw_real **data;
    int length;
    int width;
    void *callbackArgs;
    void (* callback)(void *callbackArgs, fftw_real **result, int length, int width);
} fftthreadargs;

typedef struct
{
    int *sock;
    int finished;
    int sentData;
    int *areaOfInterest;
    pthread_mutex_t lock;
} finalCallbackArgs;


#endif
