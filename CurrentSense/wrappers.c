#include "wrappers.h"

int measureWrapper  (int *sockfd, int *usbfd) {
	uint8_t	USBBufferOut[2], USBBufferIn[2];
	uint16_t	valueBuffer = 0;
	//uint16_t	value;

	memset(USBBufferOut, 0, 2);
	memset(USBBufferIn, 0, 2); // 2015-05-26: 2 was 8: would overflow USBBufferIn

	USBBufferOut[0] = 251; //Largest prime smaller than 0xff
	USBBufferIn[1]  = 0;

	ewrite(*usbfd, USBBufferOut, 2);
	if( (myReadfull(*usbfd, USBBufferIn, 2) != 2) ) {
		int32_t tmp = HARDWARE_COMM_ERR;
		char errorstring[1024];

		memset(errorstring, 0, 1024);
		sprintf(errorstring, "recvd from STM32: 0x%x 0x%x\n", USBBufferIn[0], USBBufferIn[1]);
		ewrite(*sockfd, &tmp, sizeof(int32_t));
		tmp = strlen(errorstring);
		ewrite(*sockfd, &tmp, sizeof(int32_t));

		ewrite(*sockfd, errorstring, strlen(errorstring));

		return( HARDWARE_COMM_ERR );
	} else {
		int32_t tmp[2] = {SUCCESS, sizeof(float)};
		ewrite(*sockfd, tmp, sizeof(int32_t)*2);

		valueBuffer = USBBufferIn[1];
		valueBuffer |= USBBufferIn[0] << 8;
		//memcpy( &value, &valueBuffer, 2);
		float scaledValue = 1.526e-5 * (float)valueBuffer;
		printf("measured %f mA,  %d \n", scaledValue, valueBuffer );
		ewrite(*sockfd, &scaledValue, sizeof(float));
	}
	return SUCCESS;
}

int	idWrapper( int *sockfd ) {
	int32_t tmp = SUCCESS;
	char idstring[1024];

	memset(idstring, 0, 1024);
	sprintf(idstring, "PDCurrent measurement interface\n");
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	tmp = strlen(idstring);
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	ewrite(*sockfd, idstring, strlen(idstring));

	return SUCCESS;
}
