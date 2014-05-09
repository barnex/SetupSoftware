#include "../Libraries/socket.h"
#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include "ini.h"
#include <signal.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

// These ports are SSH tunneled to mona/localhost
#define CTRLR_PORT  5000
#define TX_PORT	    5003
// These ports are SSH tunneleded to dynalab
#define FFT_PORT    5004
#define RX_PORT	    5001
#define IPD_PORT    5002

typedef struct
{
    double startFrequency;
    double stopFrequency;
    double stepFrequency;

    double startField;
    double stopField;
    double stepField;

    int nMeasurements;

    double power;
    double IF;
    double bandwidth;
    double settleTime;
    double offset;

    char savedir[1024];
} configuration;

int sockfd;

static int handler(void *user, const char *section, const char *name,
    const char *value);

int main(int argc, char **argv)
{
    configuration config;
    memset(&config, 0, sizeof(configuration));
    char *homeDir = getenv("HOME");
    assert(homeDir);
    char cfgfile[1024];
    memset(cfgfile, 0, 1024);
    sprintf(cfgfile, "%s/fmr_scanner.ini", homeDir );

    ini_parse(cfgfile, handler, &config);

    time_t current_time = time(NULL);
    char date[128];
    memset(date, 0, 128);
    strftime( date, 128, "%d_%m_%Y", localtime( &current_time ) );

    int tmp = 0;
    int lastIndex = 0;
    DIR *d;
    struct dirent *dir;
    d = opendir(config.savedir);
    char pattern[1024];
    memset(pattern, 0, 1024);
    sprintf(pattern, "%s_%%d.dat", date);
    if(d)
    {
	while((dir = readdir(d)) != NULL)
	{
	    if ( sscanf(dir->d_name, pattern, &tmp) > 0 )
	    {
		lastIndex = (tmp > lastIndex) ? tmp : lastIndex;
	    }
        }
	closedir(d);
    }

    char filename[1024];
    memset(filename, 0, 1024);
    sprintf(filename, "%s/%s_%.4d.dat",config.savedir, date, lastIndex+1);
    printf("Writing data to: %s\n", filename);
    FILE * dest = fopen(filename, "w");

    // Init the sockets
    int audioSocket = 0;
    initClient( &audioSocket, FFT_PORT);
    int HPTxSocket  = 0;
    initClient( &HPTxSocket, TX_PORT);
    int HPRxSocket  = 0;
    initClient( &HPRxSocket, RX_PORT);
    int IPDSocket = 0;
    initClient( &IPDSocket, IPD_PORT);
    int fieldSocket = 0;
    initClient( &fieldSocket, CTRLR_PORT);
    

    // Init the relevant params
    struct timespec sleeptime, remaining;
    sleeptime.tv_sec = 2;
    sleeptime.tv_nsec = (int)(config.settleTime);

    char indexFilename[1024];
    memset(indexFilename, 0, 1024);
    sprintf(indexFilename, "%s/index.txt",config.savedir);
    FILE * indexfile = fopen(indexFilename, "a");

    char *textbuffer = NULL;
    size_t size;
    printf("Please enter your comment for this measurement: ");

    fprintf( indexfile, "%s: ", filename );

    if( getline( &textbuffer, &size, stdin) != -1 )
    {
	fprintf(dest, "\n\n# %s", textbuffer);
	fprintf( indexfile, "%s", textbuffer);
    }
    else
    {
	fprintf( indexfile, "No comment\n" );
    }
   
    fclose(indexfile);

    float buffer[4] = {0.0, 0.0, 0.0, 0.0};
    int32_t returnBuffer[2] = {0, 0};
    myWrite( fieldSocket, "GET,POSITION\n" );
    myReadfull( fieldSocket, (void *)returnBuffer, sizeof(int32_t)*2 );
    assert(returnBuffer[0] == SUCCESS);
    assert(returnBuffer[1] == sizeof(float)*4);
    myReadfull( fieldSocket, (void *)buffer, sizeof(float)*4);
    
    fprintf(dest, "# Scan parameters: power %f dBm, bandwidth %f Hz, offset %f Hz\n", config.power, config.bandwidth, config.offset);
    fprintf(dest, "# Fieldstrength [T]\tFrequency[MHz]\tMag. signal\tMag. noise\tPhotodiode current [mA]\n");
    fprintf(dest, "# Position: %f, %f, %f um\n", buffer[0], buffer[1], buffer[2]);

    float freqStep  = config.stepFrequency;
    float freqStart = config.startFrequency;
    float freqStop  = config.stopFrequency;
    float freqCurrent = freqStart;
    

    float fieldStart = config.startField;
    float fieldStop = config.stopField;
    assert(fieldStop < 45.5e-3);
    float fieldStep = config.stepField;
    float currentField = fieldStart;

    float meas[3];

    // We first set the output power of the signal generators (only internal levelling is currently used)
    myWrite( HPRxSocket, "SET,POW,7.0,1.0,1.0\n" );
    myReadfull( HPRxSocket, (void *) returnBuffer, sizeof(int32_t)*2);
    assert(returnBuffer[0] == SUCCESS);
    myWrite( HPTxSocket, "SET,POW,%f,1.0,0.0\n", config.power );
    myReadfull( HPTxSocket, (void *) returnBuffer, sizeof(int32_t)*2);
    assert(returnBuffer[0] == SUCCESS);

    while( freqCurrent <= freqStop )
    {
	myWrite( HPTxSocket, "SET,FREQ,%e,%e\n", freqCurrent*1.0e6, config.offset );
	myReadfull( HPTxSocket, (void *) returnBuffer, sizeof(int32_t)*2);
	assert(returnBuffer[0] == SUCCESS);
	myWrite( HPRxSocket, "SET,FREQ,%e\n", freqCurrent*1.0e6 );
	myReadfull( HPRxSocket, (void *) returnBuffer, sizeof(int32_t)*2);
	assert(returnBuffer[0] == SUCCESS);
	currentField = fieldStart;

	while( currentField <= fieldStop )
	{
	    buffer[3] = currentField / 0.455; // Mystery value!
	    myWrite( fieldSocket, "SET,START,%f,%f,%f,%f\n", buffer[0], buffer[1], buffer[2], buffer[3]);
	    myReadfull( fieldSocket, (void *) returnBuffer, sizeof(int32_t)*2);
	    assert(returnBuffer[0] == SUCCESS);
	    myWrite( fieldSocket, "GOTO\n");
	    myReadfull( fieldSocket, (void *) returnBuffer, sizeof(int32_t)*2);
	    assert(returnBuffer[0] == SUCCESS);

	    int retval = nanosleep( &sleeptime, &remaining );
	    if( retval != 0)
	    {
		    printf("Something went wrong whilst sleeping\n");
	    }

	    myWrite( audioSocket, "MEAS,%f,%f\n", config.bandwidth, config.offset ); 
	    myReadfull( audioSocket, (void *)returnBuffer, sizeof(int32_t)*2 );
	    assert(returnBuffer[0] == SUCCESS);
	    assert(returnBuffer[1] == sizeof(float)*3);
	    myReadfull( audioSocket, (void *)meas, sizeof(float)*3);

	    
	    myWrite( IPDSocket, "MEAS\n" );
	    myReadfull( IPDSocket, (void *)returnBuffer, sizeof(int32_t)*2);
	    assert(returnBuffer[0] == SUCCESS);
	    assert(returnBuffer[1] == sizeof(float));
	    
	    float ipd = 0.0;
	    myReadfull( IPDSocket, (void *)&ipd, sizeof(float));
	    
	    // This is just here for reference
	    //fprintf(dest, "# Fieldstrength [T]\tFrequency[MHz]\tMag. signal\tMag. noise\tPhotodiode current [mA]\n");
	    fprintf(dest, "%e\t%e\t%e\t%e\t%e\n", currentField, freqCurrent , meas[1], meas[2], ipd );
	    fflush(dest);
	    
	    currentField += fieldStep;
	}

	// Ramp down the field
	while(currentField > fieldStart )
	{
	    buffer[3] = currentField / 0.455; // Mystery value!
	    myWrite( fieldSocket, "SET,START,%f,%f,%f,%f\n", buffer[0], buffer[1], buffer[2], buffer[3]);
	    myReadfull( fieldSocket, (void *) returnBuffer, sizeof(int32_t)*2);
	    assert(returnBuffer[0] == SUCCESS);
	    myWrite( fieldSocket, "GOTO\n");
	    myReadfull( fieldSocket, (void *) returnBuffer, sizeof(int32_t)*2);
	    assert(returnBuffer[0] == SUCCESS);
	    currentField -= fieldStep;
	    usleep(100000.0); // Sleep 100ms before lowering the current further
	}

	//fprintf(dest, "\n");

	freqCurrent += freqStep;
    }

  
    fclose(dest);

    // Disable output power
    myWrite( HPRxSocket, "SET,POW,7.0,0.0,1.0\n" );
    myReadfull( HPRxSocket, (void *) returnBuffer, sizeof(int32_t)*2);
    assert(returnBuffer[0] == SUCCESS);

    myWrite( HPTxSocket, "SET,POW,%f,0.0,1.0\n", config.power );
    myReadfull( HPTxSocket, (void *) returnBuffer, sizeof(int32_t)*2);
    assert(returnBuffer[0] == SUCCESS);

    // Close all sockets and let the servers know we are finished
    close(audioSocket);
    close(HPTxSocket);
    close(HPRxSocket);
    close(IPDSocket);
    close(fieldSocket);


    return EXIT_SUCCESS;
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
    else if( MATCH( "field", "start" ) )
    {
	pconfig->startField = atof(value);
    }	
    else if( MATCH( "field", "stop" ) )
    {
	pconfig->stopField = atof(value);
    }	
    else if( MATCH( "field", "step" ) )
    {
	pconfig->stepField = atof(value);
    }	
    else if( MATCH( "various", "measurements" ) )
    {
	pconfig->nMeasurements = atoi(value);
    }
    else if( MATCH("various", "save_dir") )
    {
	memmove(pconfig->savedir, value, strlen(value));
    }
    else
    {
	return 0;
    }

    return 1;
}
