#include "thread.h"


/*
 * This function accepts an array of floats on which to operate an FFT and calls a callback function
 * if the calculation is finished to process the results.
 */
void* FFTThread(void *args)
{
    fftthreadargs *data = (fftthreadargs *)args;


    if ( signal(SIGPIPE, pipe_catcher) == SIG_ERR)
    {
        printf("Could not register pipe catcher\n");
    }
    // Calculate the FFT for each channel (FFTW with OpenMP if you please)

    int i = 0 ;
    fftw_real **result = malloc(sizeof(fftw_real *)*data->width);
    for( i = 0 ; i < data->width ; i++ )
    {
	result[i] = malloc(sizeof(fftw_real)*data->length);
	rfftw_plan p;
	p = rfftw_create_plan(data->length, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);
	rfftw_one(p, data->data[i], result[i]);
	rfftw_destroy_plan(p);
    }
    
    /* Print out the magnitude of the signal at 10kHz */

    // Use the callback function to return the results
    data->callback(data->callbackArgs, result, data->length, data->width);
    for( i = 0 ; i < data->width; i++ )
    {
	free(result[i]);
    }
    free(result);

    //free(args);

    return NULL;
}

/*
 * This function will continuously look for new data and
 * calculate a FFT if enough blocks have been collected
 */
void* dataCopyThread(void* args)
{
    if ( signal(SIGPIPE, pipe_catcher) == SIG_ERR)
    {
        printf("Could not register pipe catcher\n");
    }
	dataCopyThreadData *data = (dataCopyThreadData*)args;

	pthread_mutex_t *audioLock = &(data->paCallbackData->lock);

	int oldIndex = 0;
	int newIndex = 0;

	int myOldIndex = 0;
	int myNewIndex = 0;

	while(1)
	{
	    newIndex = data->paCallbackData->in->index;
	    if( newIndex != oldIndex )
	    {
		pthread_mutex_lock (audioLock);
		copy( data->paCallbackData->in, oldIndex, newIndex, data->input );
		pthread_mutex_unlock ( audioLock );
		oldIndex = newIndex;
	    }

	    myNewIndex = data->input->index;
	    if( (myNewIndex - myOldIndex) >= data->fftsize )
	    {
		int width = data->input->width;
		fftw_real **unrolled = malloc(sizeof(fftw_real *) * width );
		int i = 0;
		for ( i = 0 ; i < width ; i++ )
		{
		    unrolled[i] = malloc(sizeof(fftw_real)*data->fftsize);
		}
		unroll(data->input, myOldIndex, data->fftsize, unrolled);

		printf("going to perform an FFT\n");

		// Fire up a thread which calculates the FFT
		pthread_t *fftThread = malloc(sizeof(pthread_t));
		fftthreadargs fftThreadArgs;
		fftThreadArgs.data = unrolled;
		fftThreadArgs.length = data->fftsize;
		fftThreadArgs.width = width;
		fftThreadArgs.callbackArgs = data->callbackArgs;
		fftThreadArgs.callback = data->callback;
		pthread_create( fftThread, NULL, FFTThread, &fftThreadArgs);
	   
		myOldIndex += data->fftsize;
		if( myOldIndex >= data->input->length )
		{
		    myOldIndex -= data->input->length;
		}
	    }
	    else if( myNewIndex < myOldIndex )
	    {
		int reallength = data->input->length - myOldIndex + myNewIndex;
		if( reallength >= data->fftsize )
		{
		    myOldIndex += data->fftsize;
		    if( myOldIndex >= data->input->length )
		    {
			myOldIndex -= data->input->length;
		    }
		}
	    }

	    usleep(10.0e3);
	}

}
