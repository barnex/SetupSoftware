#include "wrappers.h"

static int readfloats( float *floatBuffer, int *flagByte, int *usbfd)
{
    uint8_t USBBufferIn[16];
    memset( USBBufferIn, 0, 16 );
    int16_t valueBuffer = 0;

    if( (myReadfull(*usbfd, USBBufferIn, 2) != 2) && (USBBufferIn[1] != 16) )
    {
	*flagByte = USBBufferIn[0];
	return( HARDWARE_COMM_ERR );
    }
    *flagByte = USBBufferIn[0];

    if( myReadfull(*usbfd, USBBufferIn, 16) != 16 )
    {
	    return( HARDWARE_COMM_ERR );
    }
    else
    {
	for(int i = 0; i < 16; i++ )
	{
	    if( i % 2 == 0)
	    {
		valueBuffer = USBBufferIn[i];
	    }
	    else
	    {
		valueBuffer |= USBBufferIn[i] << 8;
		//memcpy( &value, &valueBuffer, 2);
		floatBuffer[i/2] = INT16_TO_FLOAT * (float)valueBuffer;
		//float scaledValue = INT16_TO_FLOAT * (float)value;
	    }
	}
    }
    return SUCCESS;

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
    uint8_t USBBufferOut[2], USBBufferIn[10];
    int32_t socketBuffer = 0;
    memset(USBBufferOut, 0, 2); 
    memset(USBBufferIn, 0, 10); 
    int tmp = 0;
    float output = 0.0;

    if( strstr(stringParam, "POSITION") != NULL )
    {
	USBBufferOut[0] = IN_CMD_GET_DAC;
	USBBufferOut[1] = 0;
	write( *usbfd, USBBufferOut, 2);
	tmp = myReadfull( *usbfd, USBBufferIn, 10);
	if( (tmp == 10) && (USBBufferIn[1] == 8) )
	{
	    socketBuffer = SUCCESS;
	    write( *sockfd, &socketBuffer, sizeof(int32_t)); 
	    socketBuffer = 4*sizeof(float);
	    write( *sockfd, &socketBuffer, sizeof(int32_t));
	    for(int i = 2; i < 10; i++ )
	    {
		if( i % 2 == 0 )
		{
		    tmp = USBBufferIn[i];
		}
		else
		{
		    tmp |= USBBufferIn[i] << 8;
		    output = ((float) tmp)/65536.0;
		    write(*sockfd, &output, sizeof(float));
		}
	    }
	}
	else
	{
	    int32_t tmp = HARDWARE_COMM_ERR;
	    char errorstring[1024];

	    memset(errorstring, 0, 1024);
	    sprintf(errorstring, "recvd from STM32: 0x%x 0x%x\n", USBBufferIn[0], USBBufferIn[1]);
	    write(*sockfd, &tmp, sizeof(int32_t));
	    tmp = strlen(errorstring);
	    write(*sockfd, &tmp, sizeof(int32_t));

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

int scan2DWrapper   (int *sockfd, int *usbfd)
{
    int32_t outputBuffer[2] = {0, 0};
    uint8_t USBBufferOut[2] = {OUT_CMD_START, 0};
    float floatBuffer[8];
    int ret = SUCCESS, flagByte = 0;
    write( *usbfd, USBBufferOut, 2 );
    while( ret == SUCCESS )
    {
	ret = readfloats( floatBuffer, &flagByte, usbfd );
	if( ret == SUCCESS )
	{
	    outputBuffer[0] = SUCCESS;
	    outputBuffer[1] = sizeof(float)*8;
	    write( *sockfd, outputBuffer, sizeof(int32_t)*2);
	    write( *sockfd, floatBuffer, sizeof(float)*8);
	}
	else
	{
	    outputBuffer[0] = ret;
	    outputBuffer[1] = 0;
	    write( *sockfd, outputBuffer, sizeof(int32_t)*2);
	    return ret;
	}
	if( flagByte == OUT_CMD_LASTPIXEL )
	{
	    ret = FINISHED;
	}
    }

    if( ret == FINISHED )
    {
	return SUCCESS;
    }
    else
    {
	return ret;
    }
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
    uint8_t	USBBufferOut[2] = {IN_CMD_GET_CHAN, 0};
    int32_t	outputBuffer[2];
    int		flagByte = 0;
    float floatBuffer[8];
    int ret = 0;
    // Ask the controller to measure once
    write( *usbfd, USBBufferOut, 2 );
    // (Try to) read the floats it returns
    ret = readfloats( floatBuffer, &flagByte, usbfd);
    // Write the result out to the socket
    if( ret == SUCCESS )
    {
	outputBuffer[0] = SUCCESS;
	outputBuffer[1] = sizeof(float)*8;
	write( *sockfd, outputBuffer, sizeof(int32_t)*2);
	write( *sockfd, floatBuffer, sizeof(float)*8);
	return SUCCESS;
    }
    else
    {
	outputBuffer[0] = ret;
	outputBuffer[1] = 0;
	write( *sockfd, outputBuffer, sizeof(int32_t)*2);
	return ret;
    }
}

int	idWrapper( int *sockfd )
{
    int32_t tmp = SUCCESS;
    char idstring[1024];

    memset(idstring, 0, 1024);
    sprintf(idstring, "STM32 Controller interface\n");
    write(*sockfd, &tmp, sizeof(int32_t));
    tmp = strlen(idstring);
    write(*sockfd, &tmp, sizeof(int32_t));
    write(*sockfd, idstring, strlen(idstring));

    return SUCCESS;
}
