#include "wrappers.h"

int measureWrapper  (int *sockfd, FILE *usbfd)
{
    fprintf(usbfd, ":MEAS:VOLT:DC?\n");
    float retval = 0.0;
    int32_t tmp[2] = {SUCCESS, sizeof(float)};
    write(*sockfd, tmp, sizeof(int32_t)*2);
    fscanf( usbfd, "%f", &retval );
    printf("measured %f V\n", retval);
    write(*sockfd, &retval, sizeof(float));
    return SUCCESS;
}

int	idWrapper( int *sockfd )
{
    int32_t tmp = SUCCESS;
    char idstring[1024];

    memset(idstring, 0, 1024);
    sprintf(idstring, "Rigol measurement interface\n");
    write(*sockfd, &tmp, sizeof(int32_t));
    tmp = strlen(idstring);
    write(*sockfd, &tmp, sizeof(int32_t));
    write(*sockfd, idstring, strlen(idstring));

    return SUCCESS;
}
