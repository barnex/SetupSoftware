# define _BSD_SOURCE
# define _POSIX_SOURCE

#include "../Libraries/io.h"
#include "../Libraries/socket.h"
#include "../Libraries/mydefs.h"
#include "../Libraries/errors.h"
#include "wrappers.h"

#define CMD_MEAS    1
#define CMD_ID	    2

int handleRequest(char *cmdbuffer, int *sockfd, int *usbfd);

int main(int argc, char **argv) {
	int usbfd = 0;
	char socketBuffer[1024];
	initSerial( &usbfd, 115200, "/dev/ttyUSB0" );
	int serverfd =  initServer( 1000 );  // TODO: port??

	while(1) {
		// Listen for incoming calls
		int clientfd = accept(serverfd, 0, 0);
		int ret = myRead( clientfd, socketBuffer, 1024 );
		while( ret > 0 ) {
			handleRequest(socketBuffer, &clientfd, &usbfd);
			ret = myRead(clientfd, socketBuffer, 1024);
		}
		close(clientfd);
	}

	return EXIT_SUCCESS;
}

int handleRequest(char *cmdbuffer, int *sockfd, int *usbfd) {
	char *localCopy = NULL, *request = NULL;
	int command = 0;
	int32_t returnValue = 0;

	// Make a local copy of the command string for parsing
	localCopy = malloc(strlen(cmdbuffer)+1);
	strcpy( localCopy, cmdbuffer );

	// Set all parameters to zero
	request = strtok(localCopy , ",");

	// See what command has been given
	if( request != NULL ) {
		if( strstr(request, "MEAS") != NULL ) {
			command = CMD_MEAS;
		} else if( strstr(request, "ID") != NULL ) {
			command = CMD_ID;
		} else {
			returnValue = UNKNOWN_COMMAND;
			ewrite(*sockfd, &returnValue, sizeof(int32_t));
			int32_t length = 0;
			ewrite(*sockfd, &length, sizeof(int32_t));
			return(returnValue);
		}
	}

	free(localCopy);

	switch(command) {
	case CMD_MEAS:
		returnValue = measureWrapper(sockfd, usbfd);
		break;
	case CMD_ID:
		returnValue = idWrapper(sockfd);
		break;
	}
	return returnValue;
}

