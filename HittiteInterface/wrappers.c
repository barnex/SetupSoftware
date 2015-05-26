#include "wrappers.h"

int setWrapper( char *stringParam, double *value, int *sockfd, FILE *hittite) {
	if( strstr(stringParam, "FREQ") != NULL ) {
		char cmdString[256];
		memset(cmdString, 0, 256);
		sprintf(cmdString, "freq %e\n", value[0]+value[1]);
		//getFrequencyString((double) value[0], (double) value[1], cmdString);
		printf("%d, %e, %s\n", (int) value[0], value[1], cmdString);
		fprintf(hittite, cmdString);
		//gpib_write( gpib, strlen(cmdString), cmdString);
	} else if(strstr(stringParam, "POW") != NULL ) {
		char cmdString[256];
		memset(cmdString, 0, 256);
		if(value[1] == 0) {
			sprintf(cmdString, "outp off\n");
			fprintf(hittite, cmdString);
		} else {
			sprintf(cmdString, "outp on\n");
			fprintf(hittite, cmdString);
			memset(cmdString, 0, 256);
			sprintf(cmdString, "pow %f\n", value[0]);
			fprintf(hittite, cmdString);
		}

		//getPowerString(value[0], (int)value[1], (int)value[2], cmdString);
		//gpib_write( gpib, strlen(cmdString), cmdString);
	} else {
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

int	idWrapper( int *sockfd ) {
	int32_t tmp = SUCCESS;
	char idstring[1024];

	memset(idstring, 0, 1024);
	sprintf(idstring, "Hittite HMC-T2100 controller\n");
	write(*sockfd, &tmp, sizeof(int32_t));
	tmp = strlen(idstring);
	write(*sockfd, &tmp, sizeof(int32_t));
	write(*sockfd, idstring, strlen(idstring));

	return SUCCESS;
}
