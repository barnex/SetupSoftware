#include "portaudio.h"
#include "mona.h"
#include "ringbuffer.h"
#include "thread.h"

#include "../Libraries/errors.h"
#include "../Libraries/io.h"
#include "../Libraries/socket.h"


/*
 * This function gets called when the input and/or output buffer is (almost) empty
 * and data needs to be shipped in and out.
 */
static int myPACallback(const void *inputBuffer, void *outputBuffer,
			unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData );

/*
 * This function get's called when the FFT has been performed to write away the
 * data.
 */
void* writeToClient(void *callbackArgs, fftw_real **result, int length, int width)

int initPortaudio(PAStream *stream, int deviceID, int framesPerBuffer, PACallbackData *userData)

int main(int argc, char **argv)
{
    int sockfd = 0;
    initServer( *sockfd, atoi(argv[1]) );

    PaStream *stream;
	
    // This is the number of (ADC) samples that are placed in the I/O buffer of the soundcard
    // When these buffers are full/empty a callback method is called to empty/fill them again
    // Data as copied in chunks this size into the primary ringbuffer
    int framesPerBuffer = 480;
    float *signalOut = malloc(sizeof(float)*framesPerBuffer);

    float t = 0.0;
    for(i = 0; i < framesPerBuffer; i++)
    {
    	t = (float)i / (float)SAMPLE_RATE;
    	signalOut[i] = sin(2.0*M_PI*1000.0*t);	
    }

    initPortaudio( stream, 2, 480, PACallbackArgs );

    // This is the callback-function that PortAudio call's when the data is ready
    PACallbackData PACallbackArgs;
    ringBuffer primaryRB;
    initRingBuffer(&primaryRB, 16384, 2);
    PACallbackArgs.out = signalOut;
    PACallbackArgs.in = &primaryRB; // The input from the soundcard in copied into this primary ringbuffer
    PACallbackArgs.discard = 1;
    pthread_mutex_init( &(callbackArgs.lock), NULL);

    ringBuffer FFTbuffer;	    // Data is copied from the primary ringbuffer into this ringbuffer
    pthread_t dataCopyThread;	    // This thread will be created when a FFT is requested
    CopyThreadData copyThreadArgs;  // This thread requires some arguments which are grouped together here
    copyThreadArgs.paCallbackData = &PACallbackArgs; // Data will be coming from the primary ringbuffer (watch the mutex lock!)
    copyThreadArgs.input = &FFTbuffer;	// Data will be copied to the FFT ringbuffer
    pthread_mutex_init( &(copyThreadArgs.threadlock), NULL); // This mutex will be locked in order not to kill the thread before all
							    // data is shipped out.
    Pa_StartStream( stream );
    
    while(1)
    {
	/* Listen for incoming calls */
	newsockfd = accept(sockfd, 0, 0);
		    args.sock = &newsockfd;
		    bzero(buffer, 256);
		    int ret = 0;
		    ret = read(newsockfd, buffer, 256);
		    int stop = 0;
		    while( ret > 0 )
		    {
			int FFTSIZE = atoi(strtok(buffer, ","));
			args.areaOfInterest[0] = atof(strtok(NULL, ","));
			args.areaOfInterest[1] = atof(strtok(NULL, ","));
			args.areaOfInterest[2] = atof(strtok(NULL, ","));
			args.areaOfInterest[3] = atof(strtok(NULL, ","));

			initRingBuffer(&FFTbuffer, FFTSIZE*2, 2);
			CopyThreadArgs.fftsize = FFTSIZE;
			double measureTime = 1.2e3 * (double)FFTSIZE/(double)SAMPLE_RATE + 50.0;
			printf("measureTime = %f\n", measureTime);
			printf("Starting recording\n");
			pthread_create( &dataCopyThreadThread, NULL, dataCopyThread, &dataCopyThreadArgs);

			callbackArgs.discard = 0;

			Pa_Sleep( (long) measureTime );

			printf("finished recording\n");

			
			while( args.sentData == 0 )
			{
			    Pa_Sleep( 100 );
			}
			callbackArgs.discard = 1;
			args.sentData = 0;

			pthread_mutex_lock( &(args.lock) );
			
			pthread_cancel( dataCopyThreadThread );
			bzero(buffer, 256);
			sprintf(buffer, "EOM");
			write(newsockfd, buffer, 64);
			reset( &primaryRB );
			reset( &FFTbuffer );
			freeRingBuffer(&FFTbuffer);
			pthread_mutex_unlock( &(args.lock) );
			ret = read(newsockfd, buffer, 256);
			stop = (strstr(buffer, "STOP") != NULL);
		    }
		    printf("Closing connection\n");
		    close( newsockfd );
		}
		else
		{
		    printf("Forbidden client\n");
		}
	}
	Pa_StopStream( stream );
	printf("Stopping recording\n");

	Pa_CloseStream( stream );

	Pa_Terminate();

	freeRingBuffer(&primaryRB);

	return EXIT_SUCCESS;
}

int initPortaudio(int deviceID, int framesPerBuffer, PACallbackData *userData)
{
    // Initialize PortAudio
    Pa_Initialize();
    if ( signal(SIGPIPE, pipe_catcher) == SIG_ERR)
    {
	printf("Could not register pipe catcher\n");
    }


    PaStreamParameters outputParameters;
    PaStreamParameters inputParameters;
    bzero( &inputParameters, sizeof(inputParameters));
    bzero( &outputParameters, sizeof(outputParameters));

    inputParameters.channelCount = 2;
    inputParameters.device = deviceID;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(0)->defaultLowInputLatency;

    outputParameters.channelCount = 1;
    outputParameters.device = 2;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(0)->defaultLowInputLatency;

    PaError err = Pa_IsFormatSupported( &inputParameters, &outputParameters, SAMPLE_RATE);
    if( err != paFormatIsSupported )
    {
	printf("Format not supported\n");
	return(EXIT_FAILURE);
    }
	
    Pa_OpenStream( &stream, &inputParameters, &outputParameters, SAMPLE_RATE, framesPerBuffer, paNoFlag, mypaCallback, userData);
    return EXIT_SUCCESS;
}

static int myPACallback(const void *inputBuffer, void *outputBuffer,
			unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData )
{
	// Default pointer conversion, no explicit check for size
	PACallbackData *data = (PACallbackData *)userData;
	memcpy(outputBuffer, data->out, framesPerBuffer*sizeof(float));
    
	// If data needs not be discarded...
	if( data->discard == 0 )
	{
	    // Lock the mutex so we can safely add the data
	    pthread_mutex_lock( &(data->lock) );
	    // Deinterleave (opt.) the data into the ringbuffer
	    deinterleave( inputBuffer, framesPerBuffer, data->in );
	    // Free the mutex
	    pthread_mutex_unlock( &(data->lock) );
	    // Show that new data has been processed
	    data->toggleFlag *= -1;
	}

	return 0;
}

void* writeToClient(void *callbackArgs, fftw_real **result, int length, int width)
{

    /* It's a pointer conversion */

    finalCallbackArgs * args = (finalCallbackArgs *)callbackArgs;
    if ( signal(SIGPIPE, pipe_catcher) == SIG_ERR)
    {
        printf("Could not register pipe catcher\n");
    }
    printf("Starting final callback\n");
    // Lock a mutex so the thread does not get killed before it's finished
    pthread_mutex_lock( &(args->lock) );
   
}
