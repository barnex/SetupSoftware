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
    uint8_t outputBuffer[10];
    memset(outputBuffer, 0, 10); 

    if( strstr(stringParam, "START") != NULL )
    {
	outputBuffer[0] = IN_CMD_SET_START;
	outputBuffer[1] = 8;
	for(int i = 0; i < 8; i++ )
	{
	    uint32_t tmp = (uint32_t) ( 65535.0 * parameters[i/2] );
	    if( i % 2 == 0 )
	    {
		outputBuffer[i+2] = (uint8_t) (tmp & 0xff);
	    }
	    else
	    {
		outputBuffer[i+2] = (uint8_t) ((tmp >> 8) & 0xff);
	    }
	}
	write( *usbfd, outputBuffer, 10 );
    }
    else if(strstr(stringParam, "POSITION") != NULL )
    {
	outputBuffer[0] = IN_CMD_GOTO;
	outputBuffer[1] = 8;
	for(int i = 0; i < 8; i++ )
	{
	    uint32_t tmp = (uint32_t) ( 65535.0 * parameters[i/2] );
	    if( i % 2 == 0 )
	    {
		outputBuffer[i+2] = (uint8_t) (tmp & 0xff);
	    }
	    else
	    {
		outputBuffer[i+2] = (uint8_t) ((tmp >> 8) & 0xff);
	    }
	}
	write( *usbfd, outputBuffer, 10 );
    }else if( strstr(stringParam, "IINC") != NULL )
    {
	outputBuffer[0] = IN_CMD_SET_IINC;
	outputBuffer[1] = 8;
	for(int i = 0; i < 8; i++ )
	{
	    uint32_t tmp = (uint32_t) ( 65535.0 * parameters[i/2] );
	    if( i % 2 == 0 )
	    {
		outputBuffer[i+2] = (uint8_t) (tmp & 0xff);
	    }
	    else
	    {
		outputBuffer[i+2] = (uint8_t) ((tmp >> 8) & 0xff);
	    }
	}
	write( *usbfd, outputBuffer, 10 );

    }else if( strstr(stringParam, "JINC") != NULL )
    {
	outputBuffer[0] = IN_CMD_SET_JINC;
	outputBuffer[1] = 8;
	for(int i = 0; i < 8; i++ )
	{
	    uint32_t tmp = (uint32_t) ( 65535.0 * parameters[i/2] );
	    if( i % 2 == 0 )
	    {
		outputBuffer[i+2] = (uint8_t) (tmp & 0xff);
	    }
	    else
	    {
		outputBuffer[i+2] = (uint8_t) ((tmp >> 8) & 0xff);
	    }
	}
	write( *usbfd, outputBuffer, 10 );

    }else if( strstr(stringParam, "TSETTLE") != NULL )
    {
	outputBuffer[0] = IN_CMD_SET_TSETTLE;
	outputBuffer[1] = 2;
	uint32_t tmp = (uint32_t) parameters[0];
	outputBuffer[2] = (uint8_t) (tmp & 0xff);
	outputBuffer[3] = (uint8_t) ((tmp >> 8) & 0xff);
	write( *usbfd, outputBuffer, 4);

    }else if( strstr(stringParam, "PIXELS") != NULL )
    {
	outputBuffer[0] = IN_CMD_SET_PIXELS;
	outputBuffer[1] = 2;
	uint32_t tmp = (uint32_t) parameters[0];
	outputBuffer[2] = (uint8_t) (tmp & 0xff);
	outputBuffer[3] = (uint8_t) ((tmp >> 8) & 0xff);
	write( *usbfd, outputBuffer, 4);

    }else
    {
	int32_t tmp = UNKNOWN_PARAMETER;
	write(*sockfd, &tmp, sizeof(int32_t));
	tmp = 0;
	write(*sockfd, &tmp, sizeof(int32_t));
	return( UNKNOWN_PARAMETER );
    }

    int32_t tmp = SUCCESS;
    write(*sockfd, &tmp, sizeof(int32_t));
    tmp = 0;
    write(*sockfd, &tmp, sizeof(int32_t));

    return SUCCESS;
}

int getWrapper	    (char *stringParam, int *sockfd, int *usbfd)
{
    uint8_t outputBuffer[2], inputBuffer[10];
    int32_t socketBuffer = 0;
    memset(outputBuffer, 0, 2); 
    memset(inputBuffer, 0, 10); 
    int tmp = 0;
    float output = 0.0;

    if( strstr(stringParam, "POSITION") != NULL )
    {
	outputBuffer[0] = IN_CMD_GET_DAC;
	outputBuffer[1] = 0;
	write( *usbfd, outputBuffer, 2);
	if( readfull( *usbfd, inputBuffer, 10 ) == 10 && (inputBuffer[1] == 8) )
	{
	    socketBuffer = SUCCESS;
	    write( *sockfd, &socketBuffer, sizeof(int32_t)); 
	    socketBuffer = 4*sizeof(float);
	    write( *sockfd, &socketBuffer, sizeof(int32_t));
	    for(int i = 2; i < 10; i++ )
	    {
		if( i % 2 == 0 )
		{
		    tmp = inputBuffer[i];
		}
		else
		{
		    tmp |= inputBuffer[i] << 8;
		    output = INT16_TO_FLOAT * (float) tmp;
		    write(*sockfd, &output, sizeof(float));
		}
	    }
	}
	else
	{
	    int32_t tmp = HARDWARE_COMM_ERR;
	    char errorstring[1024];

	    memset(errorstring, 0, 1024);
	    write(*sockfd, &tmp, sizeof(int32_t));
	    tmp = strlen(errorstring);
	    write(*sockfd, &tmp, sizeof(int32_t));

	    sprintf(errorstring, "recvd from STM32: 0x%x 0x%x\n", inputBuffer[0], inputBuffer[1]);
	    write(*sockfd, errorstring, strlen(errorstring));

	    return( HARDWARE_COMM_ERR );
	}
    }else
    {
	int32_t tmp = UNKNOWN_PARAMETER;
	write(*sockfd, &tmp, sizeof(int32_t));
	tmp = 0;
	write(*sockfd, &tmp, sizeof(int32_t));
	return( UNKNOWN_PARAMETER );
    }

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
    uint8_t outputBuffer[2] = { IN_CMD_RESET, 0 };
    write( *usbfd, outputBuffer, 2 );
    int32_t socketOutput[2] = { SUCCESS, 0 };
    write( *sockfd, socketOutput, 2*sizeof(int32_t));
    return SUCCESS;
}
int abortWrapper    (int *sockfd, int *usbfd)
{
    uint8_t outputBuffer[2] = { IN_CMD_ABORT, 0 };
    write( *usbfd, outputBuffer, 2 );
    int32_t socketOutput[2] = { SUCCESS, 0 };
    write( *sockfd, socketOutput, 2*sizeof(int32_t));
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
