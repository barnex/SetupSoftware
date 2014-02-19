#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "wrappers.h"

#ifdef _USE_ARDUINO
#include "gpib.h"
#endif

#include "../Libraries/errors.h"
#include "../Libraries/io.h"
#include "../Libraries/socket.h"

#ifndef _GPIB_LISTENER
#define _GPIB_LISTENER 2
#endif

#ifndef _LISTEN_TO_PORT
#define _LISTEN_TO_PORT 1001
#endif

#define CMD_SET	    1
#define CMD_ID	    8

#define MAX_PARAMS  1

#ifdef _USE_ARDUINO
int handleRequest( char *cmdbuffer, int *clientfd, gpibio *gpib);
#else
#ifdef _USE_PROLOGIX
int handleRequest( char *cmdbuffer, int *clientfd, int *gpib);
#endif
#endif

int main(int argc, char **argv)
{
#ifdef _USE_ARDUINO
    // Basic init
    gpibio *gpib = gpib_init(0x00, 0x01, "/dev/ttyACM0");
    assert( gpib != NULL );
    assert( gpib_ping(gpib) != 0 );

    // Resetting GPIB bus
    gpib_remote(gpib, 1);
    gpib_clear(gpib, 1);
    gpib_untalk(gpib);
    gpib_unlisten(gpib);
    gpib_talker( gpib, 0x00 );
    gpib_listener( gpib, _GPIB_LISTENER );
#else
#ifdef _USE_PROLOGIX
    int *gpib = 0;
    initRemoteClient( gpib, "192.168.0.103", 1234 );    

    char buffer[256];
    memset(buffer, 0, 256);
    sprintf(buffer, "++mode 1\r\n");
    write(*gpib, buffer, strlen(buffer));

    memset(buffer, 0, 256);
    sprintf(buffer, "++auto 0\r\n");
    write(*gpib, buffer, strlen(buffer));

    memset(buffer, 0, 256);
    sprintf(buffer, "++addr 4\r\n");
    write(*gpib, buffer, strlen(buffer));
#endif
#endif

    char socketBuffer[1024];
    int sockfd = 0;
    initServer( &sockfd, _LISTEN_TO_PORT );

    while(1)
    {
	int clientfd = accept(sockfd, 0, 0);
	int ret = myRead( clientfd, socketBuffer, 1024 );
        while( ret > 0 )
        {
	    handleRequest(socketBuffer, &clientfd, gpib);
            ret = myRead(clientfd, socketBuffer, 1024);
        }
        close(clientfd);

    }

    return EXIT_SUCCESS;	
}

#ifdef _USE_ARDUINO
int handleRequest( char *cmdbuffer, int *clientfd, gpibio *gpib)
#else
#ifdef _USE_PROLOGIX
int handleRequest( char *cmdbuffer, int *clientfd, int *gpib)
#endif
#endif
{
    char *localCopy = NULL, *request = NULL, *stringParam = NULL;
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
	if( strstr(request, "SET") != NULL )
	{
	    command = CMD_SET;
	}
	else if( strstr(request, "ID") != NULL )
	{
	    command = CMD_ID;
	}
	else
	{
	    returnValue = UNKNOWN_COMMAND;
	    write(*clientfd, &returnValue, sizeof(int32_t));
	    int32_t length = 0;
	    write(*clientfd, &length, sizeof(int32_t));
	    return(returnValue);
	}
    }

    // If SET has been issued, the parameter name and respective value should have been received
    if( command == CMD_SET )
    {
	request = strtok(NULL, ",");
	if( request != NULL )
	{
	    stringParam = malloc(strlen(request)+1);
	    strcpy( stringParam, request );
	}
	else
	{
	    returnValue = NOT_ENOUGH_PARAMETERS;
	    write(*clientfd, &returnValue, sizeof(int32_t));
	    int32_t length = 0;
	    write(*clientfd, &length, sizeof(int32_t));
	    return(returnValue);
	}
	
	if( command == CMD_SET )
	{
	    int i = 0;
	    request = strtok(NULL, ",");
	    while( request != NULL && i < MAX_PARAMS )
	    {
		parameters[i] = atof(request);
		i++;
		request = strtok(NULL, ",");
	    }     

	    if( i == 0 )
	    {
		returnValue = NOT_ENOUGH_PARAMETERS;
		write(*clientfd, &returnValue, sizeof(int32_t));
		int32_t length = 0;
		write(*clientfd, &length, sizeof(int32_t));
		return(returnValue);
	    }
	}
    }
    free(localCopy); 

    switch(command)
    {
	case CMD_SET:	    returnValue = setWrapper(stringParam, parameters[0], clientfd, gpib);
			    free(stringParam);
			    break;
	case CMD_ID:	    returnValue = idWrapper(clientfd);
			    break;
    }
    return returnValue;
}


