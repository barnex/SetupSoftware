#include "wrappers.h"

int measureWrapper  (float *parameters, int *sockfd, handleData *args)
{
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
 
    for(int i = 0 ; i < nSamples; i++ )
    {
	input[i] = (fftw_real) paArgs->buffer[i];
    }

    // Stop the stream and unlock the mutex
    Pa_StopStream( stream );
    
    pthread_mutex_unlock( paArgs->lock );
   

    // Calculate the FFT
    rfftw_one(p, input, result);
    rfftw_destroy_plan(p);
    
    // Let the client know that we have succeeded and are ready to copy the data
    int32_t socketbuffer[2] = { SUCCESS, (nSamples/2)*sizeof(float)*3 };
    write(*sockfd, socketbuffer, sizeof(int32_t)*2);


    float databuffer[3], bandwidth = 0;
    bandwidth = (float)SAMPLE_RATE / (float)nSamples;
    memset(databuffer, 0, 3*sizeof(float));
    databuffer[0] = 0.0;
    databuffer[1] = (float) result[0];
    databuffer[2] = 0.0;
    write( *sockfd, databuffer, sizeof(float)*3);

    for(int i = 1; i < nSamples/2; i++ )
    {
	memset(databuffer, 0, 3*sizeof(float));
	databuffer[0] = bandwidth * (float)i;
	databuffer[1] = (float) result[i];
	databuffer[2] = (float) result[nSamples-i];
	write( *sockfd, databuffer, sizeof(float)*3);
    }

    free(result); 
    free(input);
    free(paArgs->buffer);
    
    return SUCCESS;
}

int	idWrapper( int *sockfd )
{
    int32_t tmp = SUCCESS;
    char idstring[1024];

    memset(idstring, 0, 1024);
    sprintf(idstring, "Audio FFT interface\n");
    write(*sockfd, &tmp, sizeof(int32_t));
    tmp = strlen(idstring);
    write(*sockfd, &tmp, sizeof(int32_t));
    write(*sockfd, idstring, strlen(idstring));

    return SUCCESS;
}
