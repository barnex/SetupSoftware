#include "controller.h"

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

int abortscan(int fd)
{
    uint8_t out[2];
    out[0] = IN_CMD_ABORT;
    out[1] = 0;

    return write(fd, out, 2);
}

int reset(int fd)
{
    uint8_t out[2];
    out[0] = IN_CMD_RESET;
    out[1] = 0;
    char buffer[64];
    memset(buffer, 0, 64);
     
    write(fd, out, 2);
    readfull(fd, (uint8_t *)buffer, 15);
    printf("Controller said: %s", buffer);
    return 0;
}

int setStart(int fd, int *start)
{
    uint8_t out[10];
    out[0] = IN_CMD_SET_START;
    out[1] = 8;
    for(int i = 0 ; i < 8; i++ )
    {
	if( i % 2 == 0 )
	{
	    out[i+2] = (uint8_t)(start[i/2] & 0x00ff);
	}
	else
	{
	    out[i+2] = (uint8_t)(start[i/2] >> 8);
	}
    }
    return write(fd, out, 10);
}
int setIInc(int fd, int *i_inc)
{
    uint8_t out[10];
    out[0] = IN_CMD_SET_IINC;
    out[1] = 8;
    for(int i = 0 ; i < 8; i++ )
    {
	if( i % 2 == 0 )
	{
	    out[i+2] = (uint8_t)(i_inc[i/2] & 0x00ff);
	}
	else
	{
	    out[i+2] = (uint8_t)(i_inc[i/2] >> 8);
	}
    }
    return write(fd, out, 10);
}
int setJInc(int fd, int *j_inc)
{
    uint8_t out[10];
    out[0] = IN_CMD_SET_JINC;
    out[1] = 8;
    for(int i = 0 ; i < 8; i++ )
    {
	if( i % 2 == 0 )
	{
	    out[i+2] = (uint8_t)(j_inc[i/2] & 0x00ff);
	}
	else
	{
	    out[i+2] = (uint8_t)(j_inc[i/2] >> 8);
	}
    }
    return write(fd, out, 10);
}

int setTSettle(int fd, int t_settle)
{
    uint8_t out[10];
    out[0] = IN_CMD_SET_TSETTLE;
    out[1] = 2;
    out[2] = (uint8_t)(t_settle & 0xff);
    out[3] = (uint8_t)(t_settle >> 8);
    return write(fd, out, 4);
}

int setPixels(int fd, int pixels)
{
    uint8_t out[10];
    out[0] = IN_CMD_SET_PIXELS;
    out[1] = 2;
    out[2] = (uint8_t)(pixels & 0xff);
    out[3] = (uint8_t)(pixels >> 8);
    return write(fd, out, 4);
}

int getPosition(int fd, int *position)
{
    uint8_t out[2], in[10];
    out[0] = IN_CMD_GET_DAC;
    out[1] = 0;    
    write(fd, out, 2);
    readfull(fd, in, 10);
    if( in[1] == 8 )
    {
	for(int i = 2 ; i < 10; i++)
	{
	    if( i % 2 == 0 )
	    {
		position[i/2 - 1] = in[i];
	    }
	    else
	    {
		position[i/2 - 1] |= in[i] << 8;
	    }
	}
	return 10;
    }
    else
    {
	return -1;
    }
}

int getChannels(int fd, int16_t *values)
{
    uint8_t out[2], in[18];
    uint16_t tmp_in;
    out[0] = IN_CMD_GET_CHAN;
    out[1] = 0;    
    write(fd, out, 2);
    readfull(fd, in, 2);
    if( in[1] == 16 )
    {
	readfull(fd, in, 16);
	printf("bytes received: ");
	for(int i = 0 ; i < 16; i++)
	{
	    printf("0x%x ", in[i]);
	    if( i % 2 == 0 )
	    {
		tmp_in = in[i];
	    }
	    else
	    {
		tmp_in |= in[i] << 8;
		memcpy( &(values[i/2]), &tmp_in, 2);
	    }
	}
	return 16;
    }
    else
    {
	return -1;
    }
}

int gotoPosition(int fd, int *position)
{
    uint8_t out[10];
    out[0] = IN_CMD_GOTO;
    out[1] = 8;
    for(int i = 0 ; i < 8; i++ )
    {
	if( i % 2 == 0 )
	{
	    out[i+2] = (uint8_t)(position[i/2] & 0x00ff);
	}
	else
	{
	    out[i+2] = (uint8_t)(position[i/2] >> 8);
	}
    }
    return write(fd, out, 10);

}

int OneDScan(int fd, uint16_t *pixelList, int wait_time);

int TwoDScan(int fd, uint16_t *pixelList, const char *filename)
{
    uint8_t out[2];
    out[0] = IN_CMD_START; 
    out[1] = 0;
    write(fd, out, 2);

    uint8_t in[18];
    uint16_t tmp_in;
    int16_t values[8];
    int tmp = 0;

    memset(in, 0, 18);
    printf("Started reading...\n");
    readfull(fd, in, 18);
    int index = 0;
    do
    {
	for(int i = 0 ; i < 16; i++)
	{
	    if( i % 2 == 0 )
	    {
		tmp_in = in[i+2];
	    }
	    else
	    {
		tmp_in |= in[i+2] << 8;
		memcpy( &(values[i/2]), &tmp_in, 2);
	    }
	}
	tmp = values[0] + values[1] + values[2] + values[3];
	pixelList[index] = values[7];
	index++;

	memset(in, 0, 18);
	readfull(fd, in, 18);
	printf("Read: {0x%x 0x%x}\n", in[0], in[1]);
    } while( in[0] != OUT_CMD_LASTPIXEL );
    
    FILE * fileout = fopen( "tmp.gif", "w");
    createImage( fileout, pixelList, sqrt(index+1) );
    return 0;
}
