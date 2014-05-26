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

int handleRequest( char *cmdbuffer, int *clientfd, FILE *hittite);

int main(int argc, char **argv)
{
    // Basic init
    FILE * hittite = fopen("/dev/hittite", "w+");

    // Resetting GPIB bus
    fprintf(hittite, "*IDN?\n");
    char id[1024];
    fgets(id, 1023, hittite);
    printf("*IDN? : %s", id);

    char socketBuffer[1024];
    int sockfd = 0;
    initServer( &sockfd, atoi(argv[1]) );

    while(1)
    {
	int clientfd = accept(sockfd, 0, 0);
	int ret = myRead( clientfd, socketBuffer, 1024 );
        while( ret > 0 )
        {
	    printf("Received: %s\n", socketBuffer);
	    handleRequest(socketBuffer, &clientfd, hittite);
            ret = myRead(clientfd, socketBuffer, 1024);
        }
        close(clientfd);

    }

    return EXIT_SUCCESS;	
}

int handleRequest( char *cmdbuffer, int *clientfd, FILE *hittite)
{
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
	case CMD_SET:	    returnValue = setWrapper(stringParam, parameters, clientfd, hittite);
			    free(stringParam);
			    break;
	case CMD_ID:	    returnValue = idWrapper(clientfd);
			    break;
    }
    return returnValue;
}


