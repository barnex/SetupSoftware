#include "wrappers.h"

int measureWrapper  (float *parameters, int *sockfd, handleData *args) {
	printf("# Started sampling\n");
	PaStream *stream	    = args->stream;
	PACallbackData *paArgs  = args->paArgs;

	// First calculate the necessary number of samples to obtain the required bandwidth
	int nSamples = (int) ( (float)SAMPLE_RATE / parameters[0] );
	// Now round this up to the next largest power of two
	nSamples = (int) pow(2.0, ceil(log2((double)nSamples)));

	paArgs->buffer  = malloc(sizeof(float)*nSamples);
	paArgs->index   = 0;
	paArgs->maxIndex = nSamples-1;

	pthread_mutex_unlock( paArgs->lock );
	pthread_mutex_lock( paArgs->lock );

	// Start the stream
	Pa_StartStream( stream );

	// Allocate some room for the FFT
	fftw_real *result = malloc(sizeof(fftw_real)*nSamples);
	fftw_real *input  = malloc(sizeof(fftw_real)*nSamples);
	rfftw_plan p;
	p = rfftw_create_plan( nSamples, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE );
	// We wait until enough data has been written and the mutex has become unlocked.

	pthread_mutex_lock( paArgs->lock );

	for(int i = 0 ; i < nSamples; i++ ) {
		input[i] = (fftw_real) paArgs->buffer[i];
	}

	// Stop the stream and unlock the mutex
	Pa_StopStream( stream );

	pthread_mutex_unlock( paArgs->lock );

	printf("# Stopped sampling, starting FFT\n");


	// Calculate the FFT
	rfftw_one(p, input, result);
	rfftw_destroy_plan(p);

	printf("# Finished FFT, looking for peak\n");


	float bandwidth = 0, *amplitude;
	bandwidth = (float)SAMPLE_RATE / (float)nSamples;
	amplitude = malloc(sizeof(float)*(1 + nSamples/2));
	memset(amplitude, 0, sizeof(float)*(1 + nSamples/2));

	amplitude[0] = fabs( result[0] );
	for(int i = 1; i < nSamples/2; i++ ) {
		amplitude[i] = sqrt( (float)(result[i]*result[i] + result[nSamples-i]*result[nSamples-i]) );
	}

	float signalStrength = 0.0;
	float peakFrequency = parameters[1];
	int peakIndex = 0;
	int startIndex = (int) (0.99*peakFrequency / bandwidth);
	int stopIndex = (int) (1.01*peakFrequency / bandwidth);
	for(int i = startIndex; i < stopIndex; i++ ) {
		if( amplitude[i] > signalStrength ) {
			signalStrength = amplitude[i];
			peakIndex = i;
		}
	}

	float noise = 0.0;
	int N = 0;
	startIndex = (int)(0.95*peakFrequency / bandwidth );
	stopIndex = (int)(1.05*peakFrequency / bandwidth );
	for(int i = startIndex; i < stopIndex; i++ ) {
		if( i > peakIndex+1 || i < peakIndex-1 ) {
			noise += amplitude[i];
			N++;
		}
	}

	float avgNoise = noise / (float)N;
	float stdNoise = 0.0;
	for(int i = startIndex; i < stopIndex; i++ ) {
		if( i > peakIndex+1 || i < peakIndex-1 ) {
			stdNoise += (amplitude[i] - avgNoise)*(amplitude[i] - avgNoise);
		}
	}
	stdNoise /= (float)(N-1);
	stdNoise = sqrt(stdNoise);

	if( amplitude[peakIndex+1] > avgNoise + 3.0*stdNoise ) {
		signalStrength += amplitude[peakIndex+1];
	}
	if( amplitude[peakIndex-1] > avgNoise + 3.0*stdNoise ) {
		signalStrength += amplitude[peakIndex-1];
	}
	// Let the client know that we have succeeded and are ready to copy the data
	int32_t socketbuffer[2] = { SUCCESS, sizeof(float)*3 };
	ewrite(*sockfd, socketbuffer, sizeof(int32_t)*2);
	float outputBuffer[3] = { bandwidth*(float)peakIndex, signalStrength, avgNoise };
	ewrite(*sockfd, outputBuffer, sizeof(float)*3);

	printf("# Finished sending\n");

	free(result);
	free(input);
	free(amplitude);
	free(paArgs->buffer);

	return SUCCESS;
}

int	idWrapper( int *sockfd ) {
	int32_t tmp = SUCCESS;
	char idstring[1024];

	memset(idstring, 0, 1024);

	sprintf(idstring, "Audio FFT interface\n");
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	tmp = strlen(idstring);
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	ewrite(*sockfd, idstring, strlen(idstring));

	return SUCCESS;
}
