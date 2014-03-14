#include "../Libraries/socket.h"
#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include <signal.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int sockfd = 0;

    initClient( &sockfd, 5002);

    while(1)
    {
	int32_t returnValue[2] = {0, 0};
        float result = 0.0;
	myWrite( sockfd, "MEAS\n" );
        myReadfull( sockfd, (void *)returnValue, sizeof(int32_t)*2 );
	assert( returnValue[1] == sizeof(float));
        myReadfull( sockfd, (void *)&result, sizeof(float));
	printf("%e\n", result);	
	sleep(1);
    }
    close( sockfd );
    return EXIT_SUCCESS;
}
