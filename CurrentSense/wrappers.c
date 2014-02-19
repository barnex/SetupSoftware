#include "wrappers.h"

int measureWrapper  (int *sockfd, int *usbfd)
{
    uint8_t	USBBufferOut[2], USBBufferIn[2];
    uint16_t	valueBuffer = 0;
    int16_t	value;
    memset(USBBufferOut, 0, 2);
    memset(USBBufferIn, 0, 8);
    USBBufferOut[0] = 251; //Largest prime smaller than 0xff
    USBBufferIn[1]  = 0;

    write(*usbfd, USBBufferOut, 2);
    if( (myReadfull(*usbfd, USBBufferIn, 2) != 2) )
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
    else
    {
	int32_t tmp = SUCCESS;
	write(*sockfd, &tmp, sizeof(int32_t));
	tmp = sizeof(float);
	write(*sockfd, &tmp, sizeof(int32_t));
	
	valueBuffer = USBBufferIn[0];
	valueBuffer |= USBBufferIn[1] << 8;
    	memcpy( &value, &valueBuffer, 2);
    	float scaledValue = 1.526e-8 * (float)value;
    	write(*sockfd, &scaledValue, sizeof(float));
    }
    return SUCCESS;
}

int	idWrapper( int *sockfd )
{
    int32_t tmp = SUCCESS;
    char idstring[1024];

    memset(idstring, 0, 1024);
    sprintf(idstring, "PDCurrent measurement interface\n");
    write(*sockfd, &tmp, sizeof(int32_t));
    tmp = strlen(idstring);
    write(*sockfd, &tmp, sizeof(int32_t));
    write(*sockfd, idstring, strlen(idstring));

    return SUCCESS;
}