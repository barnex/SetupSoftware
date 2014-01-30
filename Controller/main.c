
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
#include "controller.h"
#include "image.h"

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

int
initServer(int *sockfd, int portno)
{
    struct sockaddr_in serv_addr;
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd <= 0) 
    {
	fprintf(stderr, "! ERROR: Could not open socket\n");
	fprintf(stderr, "!Error Message from system %s", strerror(errno));
	perror("! ERROR Message from system");
	return EXIT_FAILURE;
    }
	int iMode = 0;
	ioctl(*sockfd, FIONBIO, &iMode);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    fprintf(stdout, "Port for binding is %d\n", portno);
    serv_addr.sin_port = htons(portno);
    if (bind(*sockfd, (struct sockaddr *) &serv_addr,
	sizeof(serv_addr)) < 0)
    {
	fprintf(stderr, "! ERROR: Could not open socket!\n");
	perror("! ERROR Message from system");
	return EXIT_FAILURE;
    }
    listen(*sockfd,5);
    fprintf(stdout, "Succesfully opened socket, now listening\n");
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    char *portname = "/dev/ttyAMA0";
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
    printf("Terminal interface initialized\nPlease press enter\n");
    getchar();
    int16_t values[8];
    //getPosition(fd, values);
    //printf("Positions {%d, %d, %d, %d}\n", values[0], values[1], values[2], values[3]);
    int i = 100;
    while(i)
    {
	printf("Sending command to measure\n");
	getChannels(fd, values);
	printf("Measured: {%d, %d, %d, %d, \n", values[0], values[1], values[2], values[3]);
	printf("\t%d, %d, %d, %d} \n", values[4], values[5], values[6], values[7]);
	usleep(100000);
    }
    /*
    int sockfd = 0, newsockfd = 0;
    struct sockaddr_in cli_addr;
    socklen_t clilen;
    clilen = sizeof(cli_addr);
    char buffer[256];
    char allowed_client[256];
    memset(allowed_client, 0, 256);
    strcpy(allowed_client, argv[1]);
    
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
    int position[4] = {0, 0, 0, 0};
    initServer( &sockfd, atoi(argv[2]));
    //gotoPosition(fd, startPosition);	
    while(1)
    {
    // Listen for incoming calls
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if( newsockfd <= 0 )
	{
		perror("Blocking error:");
	}
	assert(newsockfd > 0);
	char client_ip[256];
	char client_name[256];
	memset(client_name, 0, 256);
	char serv_name[256];
	struct sockaddr_in *tmp = (struct sockaddr_in *)&cli_addr;
	inet_ntop(AF_INET, &(tmp->sin_addr), client_ip, clilen);
	getnameinfo((struct sockaddr *) &cli_addr, clilen,
	    client_name, 256,  serv_name, 256, 0);

	if( strcmp(client_name, allowed_client) == 0 )
	{
	    printf("Accepted new connection from %s\n", client_name);
	    bzero(buffer,256);
	    int ret = read(newsockfd,buffer,256);
		    printf("Incoming: %s\n", buffer );
	    while( ret > 0 && (strpbrk(buffer, "STOP") == strpbrk("a", "b") ) )
	    {
		if ( strlen(buffer) > 0 )
		{	 
		    printf("Incoming: %s\n", buffer );
			float milliAmps = atof(buffer);
			if( milliAmps < 2500.0 )
			{
				position[3] = (int)( milliAmps * 13.1072 );
				printf("Setting DAC to: %d\n", position[3]);
				gotoPosition(fd, position);
			}
		}
		memset(buffer, 0, 256);
		ret = read(newsockfd, buffer, 256);
	    }
		printf("Connection closed\n");
	}
	else
	{
	    close(newsockfd);
	}
    }

    */	
    return EXIT_SUCCESS;
}
