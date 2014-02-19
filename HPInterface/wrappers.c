#include "wrappers.h"

void getFrequencyString(double frequency, char *cmdString)
{
    uint64_t f = (uint64_t) (frequency / 1.0e3);
    uint64_t khz = ( f % 1000 );
    uint64_t mhz = ( (f - khz) % 1000000 ) /1000;
    uint64_t ghz =  (f - khz - mhz*1000)  / 1000000;

    if( ghz >= 10 )
    {
	memset(cmdString, 0, 256);
	sprintf(cmdString, "P%llu%.2lluT%llu%.3lluZ1\r\n", ghz, mhz/10, mhz % 10, khz);
    }
    else
    {
	memset(cmdString, 0, 256);
	sprintf(cmdString, "Q%llu%.2lluT%llu%.3lluZ1\r\n", ghz, mhz/10, mhz % 10, khz);
    }
}

void getPowerString(double power, char *cmdString)
{
    // empty
}

#ifdef _USE_ARDUINO
int setWrapper( char *stringParam, float value, int *sockfd, gpibio *gpib)
#else
#ifdef _USE_PROLOGIX
int setWrapper( char *stringParam, float value, int *sockfd, int *gpibsock )
#endif
#endif
{
    if( strstr(stringParam, "FREQ") != NULL )
    {
	char cmdString[256];
	getFrequencyString(value, cmdString);
#ifdef _USE_ARDUINO
	gpib_write( gpib, strlen(cmdString), cmdString);
#else
#ifdef _USE_PROLOGIX
	write( *gpibsock, cmdString, strlen(cmdString) );
#endif
#endif
    }
    else if(strstr(stringParam, "POW") != NULL )
    {
	char cmdString[256];
	getPowerString(value, cmdString);
#ifdef _USE_ARDUINO
	gpib_write( gpib, strlen(cmdString), cmdString);
#else
#ifdef _USE_PROLOGIX
	write( *gpibsock, cmdString, strlen(cmdString) );
#endif
#endif
    }
    else
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

int	idWrapper( int *sockfd )
{
    int32_t tmp = SUCCESS;
    char idstring[1024];

    memset(idstring, 0, 1024);
#ifdef _USE_ARDUINO
    sprintf(idstring, "Arduino GPIB HP 8672A controller\n");
#else
#ifdef _USE_PROLOGIX
    sprintf(idstring, "Prologix GPIB HP 8672A controller\n");
#endif
#endif
    write(*sockfd, &tmp, sizeof(int32_t));
    tmp = strlen(idstring);
    write(*sockfd, &tmp, sizeof(int32_t));
    write(*sockfd, idstring, strlen(idstring));

    return SUCCESS;
}
