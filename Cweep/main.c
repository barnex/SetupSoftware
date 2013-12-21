#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "peakfind.h"
#include "setfreqs.h"
#include "ini.h"

typedef struct
{
    double startFrequency;
    double stopFrequency;
    double stepFrequency;
    double power;
    double IF;
    double bandwidth;
    double settleTime;
    double offset;
} configuration;

static int handler(void *user, const char *section, const char *name,
    const char *value)
{
    configuration *pconfig = (configuration *)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if( MATCH("frequencies", "start") )
    {
	pconfig->startFrequency = atof(value);
    }
    else if( MATCH( "frequencies", "stop" ) )
    {
	pconfig->stopFrequency = atof(value);
    }
    else if( MATCH( "frequencies", "step" ) )
    {
	pconfig->stepFrequency = atof(value);
    }
    else if( MATCH( "frequencies", "if" ) )
    {
	pconfig->IF = atof(value);
    }
    else if( MATCH( "frequencies", "power" ) )
    {
	pconfig->power = atof(value);
    }
    else if( MATCH( "audio", "bandwidth" ) )
    {
	pconfig->bandwidth = atof(value);
    }
    else if( MATCH( "audio", "settletime" ) )
    {
	pconfig->settleTime = atof(value);
    }
    else if( MATCH( "audio", "offset" ) )
    {
	pconfig->offset = atof(value);
    }
    else
    {
	return 0;
    }

    return 1;
}


int initSockets(int *monaSock, int *hittiteSock, int *HPSock, int *rigolSock, int *vSock)
{
    /*
     * Connect to MONA over TCP
     */
    
    int sockfd = 0, portno = 2000;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	printf("Error: Could not create socket\n");
	return -1;
    }
    
    server = gethostbyname("mona.ugent.be");
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = portno;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
	printf("Error: Could not connect\n");
	return -1;
    }

    *monaSock = sockfd;
    /*
     * Connect to Raspbpi over TCP
     */
    portno = 2000;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	printf("Error: Could not create socket\n");
	return -1;
    }
    
    server = gethostbyname("pllctrl.ugent.be");
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = portno;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
	printf("Error: Could not connect\n");
	return -1;
    }

    *hittiteSock = sockfd;
    /*
     * Connect to HP 8672A over TCP
     */
    portno = 2001;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	printf("Error: Could not create socket\n");
	return -1;
    }
    
    server = gethostbyname("mona.ugent.be");
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = portno;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
	printf("Error: Could not connect\n");
	return -1;
    }

    *HPSock = sockfd;
    /*
     * connect to rigol mm over tcp
     */
    portno = 2002;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	printf("Error: Could not create socket\n");
	return -1;
    }
    
    server = gethostbyname("mona.ugent.be");
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = portno;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
	printf("Error: Could not connect\n");
	return -1;
    }


    *rigolSock = sockfd;

    /*
     * connect to Velleman over tcp
     */
    portno = 2000;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	printf("Error: Could not create socket\n");
	return -1;
    }
    
    server = gethostbyname("dynalab.ugent.be");
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = portno;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
	printf("Error: Could not connect\n");
	return -1;
    }

    *vSock= sockfd;
    return 0;
}

int main(int argc, char **argv)
{
    FILE *fileout = NULL;
    if( argc < 2 )
    {
	fileout = fopen("standard_output.txt", "a");
    }
    else
    {
	fileout = fopen(argv[1], "a");
    }
    /* Load the config file */
    configuration config;

    if( ini_parse("config.ini", handler, &config) )
    {
	printf("Could not load cweep.ini\n");
    }
    printf("Loaded ini file, start %f GHz, stop: %f GHz, bandwith %f Hz\n", config.startFrequency,
	config.stopFrequency, config.bandwidth);
    
    /* Init the sockets */
    int monaSock, hittiteSock, HPSock, rigolSock, vSock, retval = 0;
    initSockets( &monaSock , &hittiteSock, &HPSock, &rigolSock, &vSock );

    double avgNoise, stdNoise, peakValue, currentF = config.startFrequency;
    if( config.stopFrequency < config.startFrequency ){
       config.stepFrequency = -config.stepFrequency;
    }

    struct timespec sleeptime, remaining;
    sleeptime.tv_sec = 2;
    sleeptime.tv_nsec = (int)(config.settleTime);

    FILE * indexfile = fopen("index.txt", "a");
    char *textbuffer = NULL;
    size_t size;
    printf("Please enter your comment for this measurement: ");
    if( argc < 2 )
    {
	fprintf( indexfile, "standard_output.txt: ");
    }	
    else
    {
	fprintf( indexfile, "%s: ", argv[1] );
    }

    if( getline( &textbuffer, &size, stdin) != -1 )
    {
	fprintf(fileout, "\n\n# %s", textbuffer);
	fprintf( indexfile, "%s", textbuffer);
    }
    else
    {
	fprintf( indexfile, "No comment\n" );
    }
   
    fclose(indexfile);
	
    
    fprintf(fileout, "# Scan parameters: power %f dBm, bandwidth %f Hz\n", config.power, config.bandwidth);
    fprintf(fileout, "# Frequency [MHz]\tavg noise\tstd noise\tpeak value\n");

    //setHittitePwr(config.power, 1, hittiteSock);
    double highBound = 0.0;
    double lowBound = 0.0;
    if( config.stepFrequency < 0.0 )
    {
       highBound = config.startFrequency;
       lowBound = config.stopFrequency;
    } else {
       highBound = config.stopFrequency;
       lowBound = config.startFrequency;
    }
    retval = setHP(4500.0, hittiteSock);
    retval = setHP(4500.0 + config.offset/1.0e6 , HPSock);
    printf("Lower bound %f, upper bound %f, current F %f, stepf %f \n", lowBound, highBound, currentF, config.stepFrequency);
    while( currentF <= highBound && currentF >= lowBound )
    {  
	printf("Current frequency: %f MHz\n", currentF);
	retval = 0;
	char outstring[128];
	sprintf(outstring, "ISET1:%2.2f\n", currentF/1000.0);
	write(vSock, outstring, strlen(outstring));

	/*	
	do
	{
	    //retval = setHittite(currentF, hittiteSock);
	    retval = setHP(currentF, hittiteSock);
	    if( retval != 0 )
	    {
		printf("Hittite sent: %d\n", retval);
	    }
	} while(retval != 0);
	*/

    	/* Set the PLL's */

	/*
	retval = 0;
	do{
	   retval = setHP(currentF + config.offset/1.0e6 , HPSock);
	    if( retval != 0 )
	    {
		printf("Pllctrl sent: %d\n", retval);
	    }
	}while(retval != 0);
	*/
	/* Wait a short time so the LO's can settle */
	retval = nanosleep( &sleeptime, &remaining );
	if( retval != 0)
	{
		printf("Something went wrong whilst sleeping\n");
	}


	if ( getValue(monaSock, config.bandwidth, &avgNoise, &stdNoise, &peakValue, config.offset) != 0 )
        {
	   printf("Error\n");
	}
	else
        {
	    // Measure current current
	    char buffer[64];
	    bzero(buffer, 64);
	    while( strlen(buffer) < 2)
	    {
		sprintf(buffer, ":MEAS:CURR:DC?\n");
		write(rigolSock, buffer, strlen(buffer));
		bzero(buffer, 64);
		read(rigolSock, buffer, 64);
	    }
	    // Save result
	    fprintf(fileout, "%e\t%e\t%e\t%e\t%s", currentF, avgNoise, stdNoise, peakValue, buffer);
	    fflush(fileout);
        }
	

	currentF += config.stepFrequency;
    
    }
    //setHittitePwr(config.power, 0, hittiteSock);
    fclose(fileout);
    char buffer[64];
    memset( buffer, 0, sizeof(buffer) );
    sprintf(buffer, "STOP");

    /* Close all sockets and let the servers know we are finished */
    write(monaSock, buffer, 64);
    close(monaSock);
    write(hittiteSock, buffer, 64);
    close(hittiteSock);
    write(HPSock, buffer, 64);
    close(HPSock);
    write(rigolSock, buffer, 64);
    close(rigolSock);
    write(vSock, buffer, 64);
    close(vSock);

    return 0;
}
