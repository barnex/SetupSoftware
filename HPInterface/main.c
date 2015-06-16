#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "wrappers.h"

#include "../Libraries/errors.h"
#include "../Libraries/io.h"
#include "../Libraries/socket.h"

#define CMD_SET	    1
#define CMD_ID	    8

#define MAX_PARAMS  3
#define PROLOGIX_PORT 1234


static int handleRequest( char *cmdbuffer, int *clientfd, int gpib);
static void serverLoop();
static int initPrologix();


int main(int argc, char **argv) {
	setProgName(argv[0]);
	checkArgs(argc, 3, "server port(5001/5003), prologix IP address(157.193.57.199) or USB device file (/dev/...), GPIB device id (2/4)");
	char *my_port = argv[1];
	char *prologix = argv[2];
	char *gpib_id = argv[3];

	int gpib = initPrologix(prologix, atoi(gpib_id));
	serverLoop(atoi(my_port), gpib);

	return 666; // never reached
}

static void gpib_writestr(int fd, char* msg){
	gpib_write(fd, strlen(msg), msg);
}

#define BYTETOBINARYPATTERN "%d%d%d%d %d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 

static int initPrologix(char *dev, int gpib_id) {
	int fd = connect_to(dev, PROLOGIX_PORT);

	char buf[100];
	sprintf(buf, "++addr %d\n", gpib_id);
	gpib_writestr(fd, buf);
	gpib_writestr(fd, "++mode 1\n");
	gpib_writestr(fd, "++eos 3\n");
	gpib_writestr(fd, "++clr\n");

	printf("%s: polling GPIB...\n", progname);
	sprintf(buf, "++spoll %d\n", gpib_id);
	gpib_writestr(fd, buf);
	uint8_t status = 0;
	int n = read(fd, &status, 1);
	if(n != 1){
		printf("%s: could not poll GPIB\n", progname);
		abort();
	}
  	printf ("%s: serial poll status byte: "BYTETOBINARYPATTERN"\n", progname, BYTETOBINARY(status));
	//printf("%s: serial poll status byte: %d\n", progname, status);
	return fd;
}




static void serverLoop(int port, int gpib) {
	char socketBuffer[1024];
	int sockfd = initServer(port);

	while(1) {
		int clientfd = eaccept(sockfd);
		int ret = myRead( clientfd, socketBuffer, 1024 );
		while( ret > 0 ) {
			printf("%s: %s\n", progname, socketBuffer);

			handleRequest(socketBuffer, &clientfd, gpib);

			ret = myRead(clientfd, socketBuffer, 1024);
		}
		close(clientfd);

	}
}


static int handleRequest(char *cmdbuffer, int *clientfd, int gpib) {
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


