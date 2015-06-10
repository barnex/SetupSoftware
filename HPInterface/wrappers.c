#include "wrappers.h"
#include <inttypes.h>

void getFrequencyString(double frequency, double offset, char *cmdString) {
	int f = (int) (frequency/1.0e6);
	uint64_t f_off = (uint64_t) (offset);
	f_off /= 1000;
	uint64_t khz = f_off;
	uint64_t mhz = (f % 1000 );
	uint64_t ghz =  (f - mhz)  / 1000;
	printf("%"PRIu64" GHz %"PRIu64" MHz %"PRIu64" kHz\n", ghz, mhz, khz);

	if( ghz >= 10 ) {
		memset(cmdString, 0, 256);
		sprintf(cmdString, "P%"PRIu64"%.2"PRIu64"T%"PRIu64"%.3"PRIu64"Z1\r\n", ghz, mhz/10, mhz % 10, khz);
	} else {
		memset(cmdString, 0, 256);
		sprintf(cmdString, "Q%"PRIu64"%.2"PRIu64"T%"PRIu64"%.3"PRIu64"Z1\r\n", ghz, mhz/10, mhz % 10, khz);
	}
}

void getPowerString(double power, int enable, int internal, char *cmdString) {
	memset(cmdString, 0, 256);
	char rangeString[] = "0123456789:;";
	char vernierString[] = "013456789:;<=";
	char argument;
	if(!enable) {
		argument = '0';
	} else {
		if(power > 3.0) {
			if(internal) {
				argument = '3';
			} else {
				argument = '7';
			}
		} else {
			if(internal) {
				argument = '1';
			} else {
				argument = '5';
			}
		}
	}

	if( power > 3.0 ) {
		int range = (int)power / -10;
		int vernier = (-1) * (int) (power + 10.0*(double) range - 12.0);
		printf("%d\n", vernier);
		sprintf(cmdString, "K%cL%cO%c", rangeString[range], vernierString[vernier], argument);

	} else {
		int range = (int)power / -10;
		int vernier = (-1) * (int)( power + 10.0*(double)range  - 2.0);
		printf("%d\n", vernier);
		sprintf(cmdString, "K%cL%cO%c", rangeString[range], vernierString[vernier], argument);
	}
}

void gpib_write_debug(gpibio *gpib, int len, char *cmdString) {
	printf("%s: GPIB write: %s \n", progname, cmdString);
	int ret = gpib_write( gpib, len, cmdString);
	printf("%s: GPIB returned %d\n", progname, ret);
}

int setWrapper( char *stringParam, double *value, int *sockfd, gpibio *gpib) {
	if( strstr(stringParam, "FREQ") != NULL ) {
		char cmdString[256];
		getFrequencyString((double) value[0], (double) value[1], cmdString);
		printf("%d, %e, %s\n", (int) value[0], value[1], cmdString);
		gpib_write_debug(gpib, strlen(cmdString), cmdString);
	} else if(strstr(stringParam, "POW") != NULL ) {
		char cmdString[256];
		getPowerString(value[0], (int)value[1], (int)value[2], cmdString);
		gpib_write_debug( gpib, strlen(cmdString), cmdString);
	} else {
		int32_t tmp = UNKNOWN_PARAMETER;
		ewrite(*sockfd, &tmp, sizeof(int32_t));
		tmp = 0;
		ewrite(*sockfd, &tmp, sizeof(int32_t));
		return( UNKNOWN_PARAMETER );
	}

	int32_t tmp = SUCCESS;
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	tmp = 0;
	ewrite(*sockfd, &tmp, sizeof(int32_t));

	return SUCCESS;
}

int	idWrapper( int *sockfd ) {
	int32_t tmp = SUCCESS;
	char idstring[1024];

	memset(idstring, 0, 1024);
	sprintf(idstring, "Arduino GPIB HP 8672A controller\n");
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	tmp = strlen(idstring);
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	ewrite(*sockfd, idstring, strlen(idstring));

	return SUCCESS;
}
