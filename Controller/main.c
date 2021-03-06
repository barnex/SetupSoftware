# define _BSD_SOURCE
# define _POSIX_SOURCE

#include "../Libraries/io.h"
#include "../Libraries/socket.h"
#include "../Libraries/errors.h"
#include "../Libraries/mydefs.h"

#include "wrappers.h"

#include <signal.h>
#include <assert.h>

#define CMD_SET	    1
#define CMD_SCAN_2D 3
#define CMD_RESET   4
#define CMD_ABORT   5
#define CMD_MEAS    6
#define CMD_GET	    7
#define CMD_ID	    8
#define CMD_GOTO	9

#define MAX_PARAMS  4


int handleRequest(char *cmdbuffer, int sockfd, int usbfd);

//void catchBrokenpipe( int signum ) {
//	printf("Broken pipe. Will ignore\n");
//}

int main(int argc, char **argv) {
	setProgName(argv[0]);

	char socketBuffer[1024];
	int usbfd = initSerial(115200, "/dev/ttyUSB0" );
	int serverfd = initServer( atoi(argv[1]) );

	assert(signal( SIGPIPE, SIG_IGN)!=SIG_ERR);

	while(1) {
		// Listen for incoming calls
		int clientfd = eaccept(serverfd);
		int ret = myRead( clientfd, socketBuffer, 1024 );
		while( ret > 0 ) {
			printf("inbound: %s\n", socketBuffer);
			handleRequest(socketBuffer, clientfd, usbfd);
			ret = myRead(clientfd, socketBuffer, 1024);
		}
		close(clientfd);
	}

	return EXIT_SUCCESS;
}

int handleRequest(char *cmdbuffer, int sockfd, int usbfd) {
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
	if( request != NULL ) {
		if( strstr(request, "SET") != NULL ) {
			command = CMD_SET;
		} else if( strstr(request, "GET") != NULL ) {
			command = CMD_GET;
		} else if( strstr(request, "SCAN_2D") != NULL ) {
			command = CMD_SCAN_2D;
		} else if( strstr(request, "RESET") != NULL ) {
			command = CMD_RESET;
		} else if( strstr(request, "ABORT") != NULL ) {
			command = CMD_ABORT;
		} else if( strstr(request, "MEAS") != NULL ) {
			command = CMD_MEAS;
		} else if( strstr(request, "GOTO") != NULL ) {
			command = CMD_GOTO;
		} else if( strstr(request, "ID") != NULL ) {
			command = CMD_ID;
		} else {
			returnValue = UNKNOWN_COMMAND;
			ewrite(sockfd, &returnValue, sizeof(int32_t));
			int32_t length = 0;
			ewrite(sockfd, &length, sizeof(int32_t));
			return(returnValue);
		}
	}

	// If SET has been issued, the parameter name and respective value should have been received
	if( command == CMD_SET || command == CMD_GET ) {
		request = strtok(NULL, ",");
		if( request != NULL ) {
			stringParam = malloc(strlen(request)+1);
			strcpy( stringParam, request );
		} else {
			returnValue = NOT_ENOUGH_PARAMETERS;
			ewrite(sockfd, &returnValue, sizeof(int32_t));
			int32_t length = 0;
			ewrite(sockfd, &length, sizeof(int32_t));
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
				ewrite(sockfd, &returnValue, sizeof(int32_t));
				int32_t length = 0;
				ewrite(sockfd, &length, sizeof(int32_t));
				return(returnValue);
			}
		}
	}
	free(localCopy);

	switch(command) {
	case CMD_SET:
		returnValue = setWrapper(stringParam, parameters, sockfd, usbfd);
		free(stringParam);
		break;
	case CMD_SCAN_2D:
		returnValue = scan2DWrapper(sockfd, usbfd);
		break;
	case CMD_RESET:
		returnValue = resetWrapper(sockfd, usbfd);
		break;
	case CMD_ABORT:
		returnValue = abortWrapper(sockfd, usbfd);
		break;
	case CMD_MEAS:
		returnValue = measureWrapper(sockfd, usbfd);
		break;
	case CMD_GET:
		returnValue = getWrapper(stringParam, sockfd, usbfd);
		break;
	case CMD_GOTO:
		returnValue = gotoWrapper(sockfd, usbfd);
		break;
	case CMD_ID:
		returnValue = idWrapper(sockfd);
		break;
	}
	return returnValue;
}

