#include "wrappers.h"

int measureWrapper  (int *sockfd, FILE *usbfd) {
	fprintf(usbfd, ":MEAS:VOLT:DC?\n");
	float retval = 0.0;
	int32_t tmp[2] = {SUCCESS, sizeof(float)};
	ewrite(*sockfd, tmp, sizeof(int32_t)*2);
	int read = fscanf( usbfd, "%f", &retval );
	if (read < 1) {
		fatal("read from USB");
	}
	printf("%s: measured %f V\n", progname, retval);
	ewrite(*sockfd, &retval, sizeof(float));
	return SUCCESS;
}

int	idWrapper( int *sockfd ) {
	int32_t tmp = SUCCESS;
	char idstring[1024];

	memset(idstring, 0, 1024);
	sprintf(idstring, "Rigol measurement interface\n");
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	tmp = strlen(idstring);
	ewrite(*sockfd, &tmp, sizeof(int32_t));
	ewrite(*sockfd, idstring, strlen(idstring));

	return SUCCESS;
}
