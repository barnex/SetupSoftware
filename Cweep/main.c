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

    double startCurrent;
    double stopCurrent;
    double stepCurrent;

    int nMeasurements;

    double power;
    double IF;
    double bandwidth;
    double settleTime;
    double offset;
} configuration;


static int handler(void *user, const char *section, const char *name,
    const char *value);

int initSocket(int *socket, char *server_name, int portno);

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
    // Load the config file
    configuration config;

    if( ini_parse("config.ini", handler, &config) )
    {
	printf("Could not load cweep.ini\n");
    }
    printf("Loaded ini file, start %f GHz, stop: %f GHz, bandwith %f Hz\n", config.startFrequency,
	config.stopFrequency, config.bandwidth);
    
    // Init the sockets
    int audioSocket = 0;
    initSocket( &audioSocket, "mona.ugent.be", 2000);
    int HPTxSocket  = 0;
    initSocket( &HPTxSocket, "pllctrl.ugent.be", 2000);
    int HPRxSocket  = 0;
    initSocket( &HPRxSocket, "mona.ugent.be", 2001);
    int rigolSocket = 0;
    initSocket( &rigolSocket, "mona.ugent.be", 2002);
    int fieldSocket = 0;
    initSocket( &fieldSocket, "pllctrl.ugent.be", 2001);
    

    // Init the relevant params
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
    fprintf(fileout, "# Current [mA]\tFrequency[MHz]\tAVG Noise\tRMS Noise\tMagnitude sig\tPhase sig\tMagnitude ref\tPhase ref\n");


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
    
    float freqStep  = config.stepFrequency;
    float freqStart = config.startFrequency;
    float freqStop  = config.stopFrequency;
    float freqCurrent = freqStart;
    

    float currentStart	= config.startCurrent;
    float currentStop	= config.stopCurrent;
    float currentStep	= config.stepCurrent;
    float currentCurrent = currentStart;

    double * measurement = malloc(sizeof(double)*6);
    double fcenter[2] = { config.offset, 10.0e3 };

    while( freqCurrent <= freqStop )
    {
	setHP( freqCurrent, HPRxSocket );
	setHP( freqCurrent + config.offset/1.0e6, HPTxSocket );
	currentCurrent = currentStart;

	while( currentCurrent <= currentStop )
	{
	    char outstr[64];
	    memset(outstr, 0, 64);
	    sprintf(outstr, "%f\n", currentCurrent );
	    write( fieldSocket, outstr, strlen(outstr) );

	    int retval = nanosleep( &sleeptime, &remaining );
	    if( retval != 0)
	    {
		    printf("Something went wrong whilst sleeping\n");
	    }
   
	    int i = 0;
	    for( i = 0 ; i < config.nMeasurements; i++ )
	    { 
		if ( getValue(audioSocket, config.bandwidth, measurement, fcenter) != 0 )
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
			write(rigolSocket, buffer, strlen(buffer));
			bzero(buffer, 64);
			read(rigolSocket, buffer, 64);
		    }
		    // Save result
		    fprintf(fileout, "%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%s", currentCurrent, freqCurrent, measurement[0], measurement[1], 
			measurement[2], measurement[3], measurement[4], measurement[5], buffer);
		    fflush(fileout);
		}
	    }

	    currentCurrent += currentStep;
	}

	while(currentCurrent > currentStart )
	{
	    char outstr[64];
	    memset(outstr, 0, 64);
	    sprintf(outstr, "%f\n", currentCurrent );
	    write( fieldSocket, outstr, strlen(outstr) );
	    currentCurrent -= currentStep;
	    usleep(100000.0); // Sleep 100ms before lowering the current further
	}

	fprintf(fileout, "\n");

	freqCurrent += freqStep;
    }

  
    fclose(fileout);
    char buffer[64];
    memset( buffer, 0, sizeof(buffer) );
    sprintf(buffer, "STOP");

    // Close all sockets and let the servers know we are finished
    write(HPTxSocket, buffer, 64);
    close(HPTxSocket);
    write(HPRxSocket, buffer, 64);
    close(HPRxSocket);
    write(rigolSocket, buffer, 64);
    close(rigolSocket);
    write(fieldSocket, buffer, 64);
    close(fieldSocket);

    return 0;
}

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
    else if( MATCH( "current", "start" ) )
    {
	pconfig->startCurrent = atof(value);
    }	
    else if( MATCH( "current", "stop" ) )
    {
	pconfig->stopCurrent = atof(value);
    }	
    else if( MATCH( "current", "step" ) )
    {
	pconfig->stepCurrent = atof(value);
    }	
    else if( MATCH( "various", "measurements" ) )
    {
	pconfig->nMeasurements = atoi(value);
    }
    else
    {
	return 0;
    }

    return 1;
}

int initSocket(int *sock, char *server_name, int portno)
{
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	printf("Error: Could not create socket\n");
	return -1;
    }
    
    server = gethostbyname(server_name);
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

    *sock = sockfd;

    return EXIT_SUCCESS;
}
