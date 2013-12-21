#include "setfreqs.h"

int setLTC(double LO1_value, double LO2_value, int sockfd)
{
    int retval = 0;
    char buffer[128];

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%f,%f", LO1_value, LO2_value);
    write(sockfd, buffer, sizeof(buffer));

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, 64);
    retval = atoi(buffer);
    if (retval < 0 )
    {
	printf( "Error: could not set LTC6946-3 correctly, return value %d\n", retval );
    }
	
    return retval;
}

int setHittite(double value, int sockfd)
{
    int retval = 0;
    char buffer[128];

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, ":freq %f\r\n", value*1.0e6);
    write(sockfd, buffer, sizeof(buffer));

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, 64);
    retval = atoi(buffer);
    if (retval < 0 )
    {
	printf( "Error: could not set Hittite correctly, return value %d\n", retval );
    }
	
    return retval;
}

int setHittitePwr(double value, int on, int sockfd)
{
    int retval = 0;
    char buffer[128];

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, ":pow %f\r\n", value);
    write(sockfd, buffer, sizeof(buffer));

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, 64);
    retval = atoi(buffer);
    if (retval < 0 )
    {
	printf( "Error: could not set Hittite correctly, return value %d\n", retval );
    }


    memset(buffer, 0, sizeof(buffer));
    if( on == 1 )
    {
        sprintf(buffer, ":outp on\r\n");
    }
    else
    {	
	sprintf(buffer, ":outp off\r\n");
    }
    write(sockfd, buffer, sizeof(buffer));

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, 64);
    retval = atoi(buffer);
    if (retval < 0 )
    {
	printf( "Error: could not set Hittite correctly, return value %d\n", retval );
    }
	
    return retval;
}

int setHP(double value, int sockfd)
{
    int retval = 0;
    char buffer[128];

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%f\r\n", value*1.0e6);
    printf("%s\n", buffer);
    write(sockfd, buffer, sizeof(buffer));

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, 64);
    retval = atoi(buffer);
    if (retval < 0 )
    {
	printf( "Error: could not set HP correctly, return value %d\n", retval );
    }
	
    return retval;
}
