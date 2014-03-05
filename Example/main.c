#include "../Libraries/socket.h"
#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include <signal.h>
#include <math.h>
#include <assert.h>

int main(int argc, char **argv)
{
    int sockfd = 0;

    initClient( &sockfd, 5000);

    int32_t returnValue[2] = {0, 0};
    float   measurement[8];
    while(1)
    {
	myWrite( sockfd, "MEAS\n" );
	myReadfull( sockfd, (void *)returnValue, sizeof(int32_t)*2 );
	if( returnValue[1] == sizeof(float)*8 )
	{
	    myReadfull( sockfd, (void *)measurement, sizeof(float)*8 );
	    for(int i = 0; i < 4; i++ )
	    {
		printf("%f\t", measurement[i]);
	    }
	    printf("\n");
	}
    }
    close( sockfd );
    return EXIT_SUCCESS;
}
