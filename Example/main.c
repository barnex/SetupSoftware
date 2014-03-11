#include "../Libraries/socket.h"
#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include <signal.h>
#include <math.h>
#include <assert.h>

int main(int argc, char **argv)
{
    int sockfd = 0;

    initClient( &sockfd, 5001);

    int32_t returnValue[2] = {0, 0};
    float   measurement[8];
	myWrite( sockfd, "MEAS,0.1\n" );
	myReadfull( sockfd, (void *)returnValue, sizeof(int32_t)*2 );
	int i = 0;
	float resultfft[3] = {0.0, 0.0, 0.0};
	while( i < returnValue[1]/(sizeof(float)*3) )
	{
	    myReadfull( sockfd, (void *)resultfft, sizeof(float)*3 );
	    printf("%e\t%e\t%e\n", resultfft[0], resultfft[1], resultfft[2]);
	    i++;
	}
    close( sockfd );
    return EXIT_SUCCESS;
}
