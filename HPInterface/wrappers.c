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

void getPowerString(double power, int enable, int internal, char *cmdString)
{
    memset(cmdString, 0, 256);
    char rangeString[] = "0123456789:;";
    char vernierString[] = "013456789:;<=";
    char argument;
    if(!enable)
    {
        argument = '0';
    }
    else
    {
        if(power > 3.0)
        {
            if(internal)
            {
                argument = '3';
            }
            else
            {
                argument = '7';
            }
        }
        else
        {
            if(internal)
            {
                argument = '1';
            }
            else
            {
                argument = '5';
            }
        }
    }

    if( power > 3.0 )
    {
        int range = (int)power / -10;
        int vernier = (-1) * (int) (power + 10.0*(double) range - 12.0);
	printf("%d\n", vernier);
        sprintf(cmdString, "K%cL%cO%c", rangeString[range], vernierString[vernier], argument);

    }
    else
    {
        int range = (int)power / -10;
        int vernier = (-1) * (int)( power + 10.0*(double)range  - 2.0);
	printf("%d\n", vernier);
        sprintf(cmdString, "K%cL%cO%c", rangeString[range], vernierString[vernier], argument);
    }
}

int setWrapper( char *stringParam, float *value, int *sockfd, gpibio *gpib)
{
    if( strstr(stringParam, "FREQ") != NULL )
    {
	char cmdString[256];
	getFrequencyString((double) value[0], cmdString);
	gpib_write( gpib, strlen(cmdString), cmdString);
    }
    else if(strstr(stringParam, "POW") != NULL )
    {
	char cmdString[256];
	getPowerString(value[0], (int)value[1], (int)value[2], cmdString);
	gpib_write( gpib, strlen(cmdString), cmdString);
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
    sprintf(idstring, "Arduino GPIB HP 8672A controller\n");
    write(*sockfd, &tmp, sizeof(int32_t));
    tmp = strlen(idstring);
    write(*sockfd, &tmp, sizeof(int32_t));
    write(*sockfd, idstring, strlen(idstring));

    return SUCCESS;
}
