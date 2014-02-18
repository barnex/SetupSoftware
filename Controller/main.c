
# define _BSD_SOURCE
# define _POSIX_SOURCE

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include <assert.h>

#include "mydefs.h"
#include "errors.h"
#include "wrappers.h"

#define CMD_SET	    1
#define CMD_SCAN_1D 2
#define CMD_SCAN_2D 3
#define CMD_RESET   4
#define CMD_ABORT   5
#define CMD_MEAS    6

#define MAX_PARAMS  4

void set_blocking (int fd, int should_block);
int set_interface_attribs (int fd, int speed, int parity);
int handleRequest(char *cmdbuffer, int *sockfd, int *usbfd);
int initServer(int *sockfd, int portno);


int main(int argc, char **argv)
{
    char *portname = "/dev/ttyUSB0";
    char buffer[256];
    memset(buffer, 0, 256);
    int fd = open( portname, O_RDWR | O_NOCTTY | O_SYNC );
    if (fd < 0)
    {
	    printf("error %d opening %s: %s", errno, portname, strerror (errno));
	    return EXIT_FAILURE;
    }
	
    set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blockin  
    printf("Terminal interface initialized\n");

    int portno = atoi(argv[2]);
    char *allowed_client = argv[1];
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


    printf("Server interface initialized\n");
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
            bzero(buffer, 256);
            int ret = 0;
            ret = read(newsockfd, buffer, 256);
            int stop = 0;
            while( ret > 0 && !stop )
            {
		handleRequest(buffer, &newsockfd, &fd);
                ret = read(newsockfd, buffer, 256);
                stop = ( strstr(buffer, "STOP") != NULL );
            }
            printf("Done, closing socket\n");
            close(newsockfd);
	}
    }

    return EXIT_SUCCESS;
}

int handleRequest(char *cmdbuffer, int *sockfd, int *usbfd)
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
	else if( strstr(request, "SCAN_1D") != NULL )
	{
	    command = CMD_SCAN_1D;
	}
	else if( strstr(request, "SCAN_2D") != NULL )
	{
	    command = CMD_SCAN_2D;
	}
	else if( strstr(request, "RESET") != NULL )
	{
	    command = CMD_RESET;
	}   
	else if( strstr(request, "ABORT") != NULL )
	{
	    command = CMD_ABORT;
	}
	else if( strstr(request, "MEAS") != NULL )
	{
	    command = CMD_MEAS;
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
	    write(*sockfd, &returnValue, sizeof(int32_t));
	    int32_t length = 0;
	    write(*sockfd, &length, sizeof(int32_t));
	    return(returnValue);
	}

	int i = 0;
	request = strtok(NULL, ",");
	while( request != NULL && i < MAX_PARAMS )
	{
	    parameters[i] = atof(request);
	    i++;
	    strtok(NULL, ",");
	}     

	if( i == 0 )
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
	case CMD_SET:	    returnValue = setWrapper(stringParam, parameters, sockfd, usbfd);
			    free(stringParam);
			    break;
	case CMD_SCAN_1D:   returnValue = scan1DWrapper(sockfd, usbfd);
			    break;
	case CMD_SCAN_2D:   returnValue = scan2DWrapper(sockfd, usbfd);
			    break;
	case CMD_RESET:	    returnValue = resetWrapper(sockfd, usbfd);
			    break;
	case CMD_ABORT:	    returnValue = abortWrapper(sockfd, usbfd);
			    break;
	case CMD_MEAS:	    returnValue = measureWrapper(sockfd, usbfd);
			    break;
    }
    return returnValue;
}

int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // ignore break signal
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        //tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf("error %d setting term attributes", errno);
}
