#include "../Libraries/socket.h"
#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include <signal.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#define _BSD_SOURCE

int main(int argc, char **argv)
{
    int sockfd = 0;

    initClient( &sockfd, 5002);

    while(1){
	int32_t returnValue[2] = {0, 0};
        float result[8];
	myWrite( sockfd, "MEAS,1.0,18.0e3\n" );
        myReadfull( sockfd, (void *)returnValue, sizeof(int32_t)*2 );
	assert( returnValue[1] == sizeof(float));
        myReadfull( sockfd, (void *)result, sizeof(float));
	for(int i = 0 ; i < 1;  i++ )
	{
	    printf("%f\t", result[i]);
	}
	printf("\n");
	usleep(250*1000);
    }
    close( sockfd );
    return EXIT_SUCCESS;
}
