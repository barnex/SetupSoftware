
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

static int readfull(int fd, uint8_t *buffer, int n)
{
    int ret = 0, i = 0;
    ret = read(fd, buffer, n);
    if( ret >= 0 && ret != n )
    {
	i = ret;
	while(i < n && ret >= 0)
	{
	    ret = read(fd, &(buffer[i]), n-i);
	    i += ret;
	}
    }
    if( ret > 0 )
    {
	return i;
    }
    else
    {
	return ret;
    }
}

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
    printf("Terminal interface initialized\nPlease press enter\n");
    getchar();

    while(1)
    {
	char buffer = 251, input[2];
	memset(input, 0, 2);
        write(fd, &buffer, 1);
	readfull(fd, (uint8_t *)input, 2);
	uint16_t returnValue = input[0] << 8 | input[1];
        printf("Received: %d\n", returnValue);
    }

    return EXIT_SUCCESS;
}

