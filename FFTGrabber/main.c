#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "portaudio.h"

#include "../Libraries/errors.h"
#include "../Libraries/io.h"
#include "../Libraries/socket.h"

#include "main.h"
#include "wrappers.h"

#define MAX_PARAMS  1

#define CMD_MEAS    1
#define CMD_ID	    2

/*
 * This function gets called when the input and/or output buffer is (almost) empty
 * and data needs to be shipped in and out.
 */
static int myPACallback(const void *inputBuffer, void *outputBuffer,
			unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData )
{
    // Default pointer conversion, no explicit check for size
    PACallbackData *data = (PACallbackData *)userData;

    printf("callback\n");

    pthread_mutex_lock( data->lock );
    printf("callback LOCKED\n");
    
    // The number of samples that need to be copied
    int nCopy = min(framesPerBuffer, data->maxIndex - data->index);
    // Copy the data into the buffer
    memmove( &(data->buffer[data->index]), inputBuffer, nCopy*sizeof(float) );
    // Increase index with the number of samples copied
    data->index += nCopy;


    pthread_mutex_unlock( data->lock );
    printf("callback UNLOCKED\n");

    return 0;
}


int initPortaudio(PaStream *stream, int deviceID, int framesPerBuffer, PACallbackData *userData);

int handleRequest(char *cmdbuffer, int *sockfd, handleData *args);

int main(int argc, char **argv)
{
    int sockfd = 0;
    initServer( &sockfd, atoi(argv[1]) );

    // We set all variables passed to the callback function to zero
    PACallbackData paArgs;
    paArgs.buffer   = NULL;
    paArgs.index    = 0;
    paArgs.maxIndex = 0;
    paArgs.lock	    = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init( paArgs.lock, NULL );
    pthread_mutex_unlock( paArgs.lock );
    PaStream *stream = NULL;

    // We will be using device 2, which should be the Terratec card
    initPortaudio(stream, 2, 480, (void *)&paArgs);

    // When we handle a request, this is used to pass along the PaStream and the callback data
    handleData handleArgs;
    handleArgs.stream = stream;
    handleArgs.paArgs = &paArgs;

    char socketBuffer[1024];	
    while(1)
    {
	// Listen for incoming calls
	int clientfd = accept(sockfd, 0, 0);
	int ret = myRead( clientfd, socketBuffer, 1024 );
        while( ret > 0 )
        {
	    handleRequest(socketBuffer, &clientfd, &handleArgs);
            ret = myRead(clientfd, socketBuffer, 1024);
        }
        close(clientfd);
	
    }
}

int initPortaudio(PaStream *stream, int deviceID, int framesPerBuffer, PACallbackData *userData)
{
    // Initialize PortAudio
    Pa_Initialize();

    PaStreamParameters inputParameters;
    bzero( &inputParameters, sizeof(inputParameters));

    inputParameters.channelCount = 1;
    inputParameters.device = deviceID;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(0)->defaultLowInputLatency;


    PaError err = Pa_IsFormatSupported( &inputParameters, NULL, SAMPLE_RATE);
    if( err != paFormatIsSupported )
    {
	printf("Format not supported\n");
	return(EXIT_FAILURE);
    }
	
    Pa_OpenStream( &stream, &inputParameters, NULL, SAMPLE_RATE, framesPerBuffer, paNoFlag, myPACallback, userData);
    return EXIT_SUCCESS;
}


int handleRequest(char *cmdbuffer, int *sockfd, handleData *args)
{
    char *localCopy = NULL, *request = NULL;
    float parameters[MAX_PARAMS];
    int command = 0;
    int32_t returnValue = 0;

    // Make a local copy of the command string for parsing
    localCopy = malloc(strlen(cmdbuffer)+1);
    strcpy( localCopy, cmdbuffer );

    // Set all parameters to zero
    memset(parameters, 0, sizeof(float)*MAX_PARAMS);
    request = strtok(localCopy , ",");

    // See what command has been given
    if( request != NULL )
    {
	if( strstr(request, "MEAS") != NULL )
	{
	    command = CMD_MEAS;
	}
	else if( strstr(request, "ID") != NULL )
	{
	    command = CMD_ID;
	}
	else
	{
	    returnValue = UNKNOWN_COMMAND;
	    write(*sockfd, &returnValue, sizeof(int32_t));
	    int32_t length = 0;
	    write(*sockfd, &length, sizeof(int32_t));
	    return(returnValue);
	}
    }

    // If SET has been issued, the parameter name and respective value should have been received
    if( command == CMD_MEAS )
    {
	request = strtok(NULL, ",");
	if( request != NULL )
	{
	    parameters[0] = atof(request);
	}
	else
	{
	    returnValue = NOT_ENOUGH_PARAMETERS;
	    write(*sockfd, &returnValue, sizeof(int32_t));
	    int32_t length = 0;
	    write(*sockfd, &length, sizeof(int32_t));
	    return(returnValue);
	}
    }
    free(localCopy); 

    switch(command)
    {
	case CMD_MEAS:	    returnValue = measureWrapper(parameters, sockfd, args);
			    break;
	case CMD_ID:	    returnValue = idWrapper(sockfd);
			    break;
    }
    return returnValue;
}

