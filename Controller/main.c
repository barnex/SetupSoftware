#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>

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

int main(int argc, char **argv)
{
	char *portname = "/dev/ttyAMA0";
	int fd = open( portname, O_RDWR | O_NOCTTY | O_SYNC );
	if (fd < 0)
	{
        	printf("error %d opening %s: %s", errno, portname, strerror (errno));
	        return EXIT_FAILURE;
	}

	set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking (fd, 0);                // set no blocking

	printf("Everything is ready. Press ENTER to continue\n");
	getchar();
	setPixels(fd, 150);
	int startPosition[4] = {0, 128, 256, 512};
	setStart(fd, startPosition);	

	/*
	uint16_t *pixelArray;
	pixelArray = malloc(sizeof(uint16_t)*100*100);
	for(int i = 0; i < 100; i++ )
	{
	    for(int j = 0; j < 100; j++ )
	    {
		if( i % 2  == 0 )
		{
		    pixelArray[i+100*j] = UINT16_MAX;
		}
		else
		{
		    pixelArray[i+100*j] = 0;
		}
	    }
	}
	createImage( NULL, pixelArray, 100);
	*/
	return EXIT_SUCCESS;
}
