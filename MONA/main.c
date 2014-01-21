#include "portaudio.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>

#include "mona.h"
#include "ringbuffer.h"
#include "thread.h"

static int mypaCallback(const void *inputBuffer, void *outputBuffer,
			unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData );

static int mypaCallback(const void *inputBuffer, void *outputBuffer,
			unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData )
{
	// Default pointer conversion, no explicit check for size
	callbackData *data = (callbackData *)userData;
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

/*
 * This function get's called when the FFT has been performed to write away the
 * data.
 */
void* finalCallbackfunction(void *callbackArgs, fftw_real **result, int length, int width)
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
   
    // Write the data to the socket given as an argument 
    float Bandwidth = (float)SAMPLE_RATE / (float)(length);
    int *sock = args->sock;
    char buffer[64];
    bzero(buffer, 64);
    int k = 0;
    for( k = 1 ; k < (length+1)/2; ++k )
    {
	bzero(buffer, 64);
	sprintf(buffer, "%e\t%e\t%e\n", Bandwidth*((float)k), result[0][k], result[0][length-k]);
	write(*sock, buffer, 64);
    }
    bzero(buffer, 64);
    sprintf(buffer, "EOL");
    write(*sock, buffer, 64);
    printf("Finished final callback\n");
    // Show that the data has been sent
    args->sentData = 1;
    // Unlock the mutex, the thread can be safely terminated now
    pthread_mutex_unlock( &(args->lock) );
    return NULL;
}

int main(int argc, char **argv)
{
	// Initialize PortAudio
	Pa_Initialize();
	if ( signal(SIGPIPE, pipe_catcher) == SIG_ERR)
	{
	    printf("Could not register pipe catcher\n");
	}

	// Diagnostic purposes, not required
	int max = Pa_GetDeviceCount();
	int i = 0;
	for ( i = 0 ; i < max ; i++ )
	{
	    PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
	    printf("%d : %s : %d/%d\n", i, deviceInfo->name, deviceInfo->maxOutputChannels, deviceInfo->maxInputChannels);
	}

	max = Pa_GetHostApiCount();
	for ( i = 0 ; i <  max ; i++ )
	{   
	    PaHostApiInfo * hostInfo = Pa_GetHostApiInfo(i);
	    printf("%d : %s\n", i, hostInfo->name );
	
	}
	

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

	// This is the callback-function that PortAudio call's when the data is ready
	callbackData callbackArgs;
	ringBuffer primaryRB;
	initRingBuffer(&primaryRB, 16384, 1);
	callbackArgs.out = signalOut;
	callbackArgs.in = &primaryRB;
	callbackArgs.discard = 1;

	pthread_mutex_init( &(callbackArgs.lock), NULL);
	
	PaStreamParameters outputParameters;
	PaStreamParameters inputParameters;
	bzero( &inputParameters, sizeof(inputParameters));
	bzero( &outputParameters, sizeof(outputParameters));

	inputParameters.channelCount = 2;
	inputParameters.device = 2;
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


	int portno = atoi(argv[2]);
        char *allowed_client = argv[1];
	/*
	 * This part initializes the socket
	 */
	/* Create a socket to listen to (act as server) */
	int sockfd, newsockfd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
	    fprintf(stderr, "! ERROR: Could not open socket!\n");
	    perror("! ERROR Message from system");
	    return EXIT_FAILURE;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	    sizeof(serv_addr)) < 0)
	{
	    fprintf(stderr, "! ERROR: Could not open socket!\n");
	    perror("! ERROR Message from system");
	    return EXIT_FAILURE;

	}
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	Pa_OpenStream( &stream, &inputParameters, &outputParameters, SAMPLE_RATE, framesPerBuffer, paNoFlag, mypaCallback, &callbackArgs);


	//Pa_OpenDefaultStream( &stream, 1, 1, paFloat32, SAMPLE_RATE, framesPerBuffer, mypaCallback, &callbackArgs);

	pthread_t dataCopyThreadThread;
	dataCopyThreadData dataCopyThreadArgs;
	dataCopyThreadArgs.paCallbackData = &callbackArgs;
	ringBuffer FFTbuffer;
	dataCopyThreadArgs.input = &FFTbuffer;
	dataCopyThreadArgs.callback = finalCallbackfunction;
	finalCallbackArgs args;	
	args.sentData = 0;
	args.areaOfInterest = malloc(sizeof(int)*4);
	args.areaOfInterest[0] = 0;
	args.areaOfInterest[1] = 0;
	args.areaOfInterest[2] = 0;
	args.areaOfInterest[3] = 0;
	dataCopyThreadArgs.callbackArgs = &args;
	pthread_mutex_init( &(args.lock), NULL);
	Pa_StartStream( stream );

	while(1)
	{
        /* Listen for incoming calls */
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		char client_ip[256];
		char client_name[256];
		char serv_name[256];
		char buffer[256];
		struct sockaddr_in *tmp = (struct sockaddr_in *)&cli_addr;
		inet_ntop(AF_INET, &(tmp->sin_addr), client_ip, clilen);
		getnameinfo((struct sockaddr *) &cli_addr, clilen,
		    client_name, 256,  serv_name, 256, 0);
		printf("Client: %s, sockfd: %d\n", client_name, newsockfd);
		if( strcmp(client_name, allowed_client) == 0 )
		{
		    printf("I have an allowed client\n");
		    args.sock = &newsockfd;
		    bzero(buffer, 256);
		    int ret = 0;
		    ret = read(newsockfd, buffer, 256);
		    while( ret > 0 && (strpbrk( buffer, "STOP" ) == strpbrk("a", "b") ) )
		    {
			printf("%s\n", buffer);
			int FFTSIZE = atoi(strtok(buffer, ","));
			args.areaOfInterest[0] = atoi(strtok(NULL, ","));
			args.areaOfInterest[1] = atoi(strtok(NULL, ","));
			args.areaOfInterest[2] = atoi(strtok(NULL, ","));
			args.areaOfInterest[3] = atoi(strtok(NULL, ","));

			initRingBuffer(&FFTbuffer, FFTSIZE*2, 1);
			dataCopyThreadArgs.fftsize = FFTSIZE;
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
