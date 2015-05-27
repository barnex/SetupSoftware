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
#define _GPIB_LISTENER 4
#endif

#define CMD_SET	    1
#define CMD_ID	    8

#define MAX_PARAMS  3

int handleRequest( char *cmdbuffer, int *clientfd, gpibio *gpib);

int main(int argc, char **argv) {
	setProgName(argv[0]);
	checkArgs(argc, 1, "port number");
	// Basic init
	gpibio *gpib = gpib_init(0x00, 0x01, "/dev/ttyACM0"); // TODO
	assert( gpib != NULL );
	assert( gpib_ping(gpib) != 0 );

	// Resetting GPIB bus
	gpib_remote(gpib, 1);
	gpib_clear(gpib, 1);
	gpib_untalk(gpib);
	gpib_unlisten(gpib);
	gpib_talker( gpib, 0x00 );
	gpib_listener( gpib, _GPIB_LISTENER );

	char socketBuffer[1024];
	int sockfd = initServer(atoi(argv[1]) );

	while(1) {
		int clientfd = eaccept(sockfd);
		int ret = myRead( clientfd, socketBuffer, 1024 );
		while( ret > 0 ) {
			printf("Received: %s\n", socketBuffer);
			handleRequest(socketBuffer, &clientfd, gpib);
			ret = myRead(clientfd, socketBuffer, 1024);
		}
		close(clientfd);

	}

	return EXIT_SUCCESS;
}

int handleRequest( char *cmdbuffer, int *clientfd, gpibio *gpib) {
	char *localCopy = NULL, *request = NULL, *stringParam = NULL;
	double parameters[MAX_PARAMS];
	int command = 0;
	int32_t returnValue = 0;

	// Make a local copy of the command string for parsing
	localCopy = malloc(strlen(cmdbuffer)+1);
	strcpy( localCopy, cmdbuffer );

	// Set all parameters to zero
	memset(parameters, 0, sizeof(double)*MAX_PARAMS);
	request = strtok(localCopy , ",");

	// See what command has been given
	if( request != NULL ) {
		if( strstr(request, "SET") != NULL ) {
			command = CMD_SET;
		} else if( strstr(request, "ID") != NULL ) {
			command = CMD_ID;
		} else {
			returnValue = UNKNOWN_COMMAND;
			ewrite(*clientfd, &returnValue, sizeof(int32_t));
			int32_t length = 0;
			ewrite(*clientfd, &length, sizeof(int32_t));
			return(returnValue);
		}
	}

	// If SET has been issued, the parameter name and respective value should have been received
	if( command == CMD_SET ) {
		request = strtok(NULL, ",");
		if( request != NULL ) {
			stringParam = malloc(strlen(request)+1);
			strcpy( stringParam, request );
		} else {
			returnValue = NOT_ENOUGH_PARAMETERS;
			ewrite(*clientfd, &returnValue, sizeof(int32_t));
			int32_t length = 0;
			ewrite(*clientfd, &length, sizeof(int32_t));
			return(returnValue);
		}

		if( command == CMD_SET ) {
			int i = 0;
			request = strtok(NULL, ",");
			while( request != NULL && i < MAX_PARAMS ) {
				parameters[i] = atof(request);
				i++;
				request = strtok(NULL, ",");
			}

			if( i == 0 ) {
				returnValue = NOT_ENOUGH_PARAMETERS;
				ewrite(*clientfd, &returnValue, sizeof(int32_t));
				int32_t length = 0;
				ewrite(*clientfd, &length, sizeof(int32_t));
				return(returnValue);
			}
		}
	}
	free(localCopy);

	switch(command) {
	case CMD_SET:
		returnValue = setWrapper(stringParam, parameters, clientfd, gpib);
		free(stringParam);
		break;
	case CMD_ID:
		returnValue = idWrapper(clientfd);
		break;
	}
	return returnValue;
}


