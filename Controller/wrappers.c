#include "wrappers.h"

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

int setWrapper	    (char *stringParam, float *parameters, int *sockfd, int *usbfd)
{
    return SUCCESS;
}

int getWrapper	    (char *stringParam, int *sockfd, int *usbfd)
{
    return SUCCESS;
}

int scan1DWrapper   (int *sockfd, int *usbfd)
{
    return SUCCESS;
}

int scan2DWrapper   (int *sockfd, int *usbfd)
{
    return SUCCESS;
}
int resetWrapper    (int *sockfd, int *usbfd)
{
    return SUCCESS;
}
int abortWrapper    (int *sockfd, int *usbfd)
{
    return SUCCESS;
}

int measureWrapper  (int *sockfd, int *usbfd)
{
    uint8_t	USBBufferOut[2], USBBufferIn[18];
    uint16_t	valueBuffer = 0;
    int16_t	value;
    memset(USBBufferOut, 0, 2);
    memset(USBBufferIn, 0, 18);
    USBBufferOut[0] = IN_CMD_GET_CHAN;
    USBBufferIn[1]  = 0;

    write(*usbfd, USBBufferOut, 2);
    if( (readfull(*usbfd, USBBufferIn, 2) != 2) && (USBBufferIn[1] != 16) )
    {
	int32_t tmp = HARDWARE_COMM_ERR;
	write(*sockfd, &tmp, sizeof(int32_t));
	tmp = 0;
	write(*sockfd, &tmp, sizeof(int32_t));
	return(tmp);
    }

    if( readfull(*usbfd, USBBufferIn, 16) != 16 )
    {
	int32_t tmp = HARDWARE_COMM_ERR;
	write(*sockfd, &tmp, sizeof(int32_t));
	tmp = 0;
	write(*sockfd, &tmp, sizeof(int32_t));
	return(tmp);
    }
    else
    {
	int32_t tmp = SUCCESS;
	write(*sockfd, &tmp, sizeof(int32_t));
	tmp = 8*sizeof(float);
	write(*sockfd, &tmp, sizeof(int32_t));
	
	for(int i = 0; i < 16; i++ )
	{
	    if( i % 2 == 0)
	    {
		valueBuffer = USBBufferIn[i];
	    }
	    else
	    {
		valueBuffer |= USBBufferIn[i] << 8;
		memcpy( &value, &valueBuffer, 2);
		float scaledValue = INT16_TO_FLOAT * (float)value;
		write(*sockfd, &scaledValue, sizeof(float));
	    }
	}
    }
    return SUCCESS;
}
