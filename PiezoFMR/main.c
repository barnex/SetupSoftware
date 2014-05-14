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
#include <string.h>

// These ports are SSH tunneled to mona/localhost
#define CTRLR_PORT  5000
// These ports are SSH tunneleded to dynalab
#define FFT_PORT    5004
#define IPD_PORT    5002

typedef struct
{
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


    float start[4];
    float width_i;
    float width_j;
    int i_axis;
    int j_axis;
    int pixels_i;
    int pixels_j;
    int tsettle;
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
    sprintf(cfgfile, "%s/piezofmr.ini", homeDir );

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
    
    fprintf(dest, "# y[um]\tz[um]\tSignal\tNoise\tIPD\n" );

    float meas[3];

    float iinc = config.width_i / (float)config.pixels_i;
    float jinc = config.width_j / (float)config.pixels_j;

    int i = 0;
    for( i = 0 ; i < config.pixels_i ; i++ )
    {
	int j = 0;
	for( j = 0; j < config.pixels_j; j++ )
	{
	    buffer[1] = (config.start[1] + (iinc * (float)i))/20.0;
	    buffer[2] = (config.start[2] + (jinc * (float)j))/20.0;

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
	    fprintf(dest, "%e\t%e\t%e\t%e\t%e\n", 20.0*buffer[1], 20.0*buffer[2], meas[1], meas[2], ipd );
	    fflush(dest);
	    
	}
    }
  
    fclose(dest);

    // Disable output power

    // Close all sockets and let the servers know we are finished
    close(audioSocket);
    close(IPDSocket);
    close(fieldSocket);


    return EXIT_SUCCESS;
}

static int handler(void *user, const char *section, const char *name,
    const char *value)
{
    configuration *pconfig = (configuration *)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if( MATCH( "audio", "bandwidth" ) )
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
    else if( MATCH("start", "x") )
    {
        pconfig->start[0] = atof(value);
    }
    else if( MATCH("start", "y") )
    {
        pconfig->start[1] = atof(value);
    }
    else if( MATCH("start", "z") )
    {
        pconfig->start[2] = atof(value);
    }
    else if( MATCH("start", "aux") )
    {
        pconfig->start[3] = atof(value);
    }
    else if( MATCH("scan", "width_i") )
    {
        pconfig->width_i = atof(value);
    }
    else if( MATCH("scan", "width_j") )
    {
        pconfig->width_j = atof(value);
    }
    else if( MATCH("scan", "i_axis") )
    {
        pconfig->i_axis = atoi(value);
    }
    else if( MATCH("scan", "j_axis") )
    {
        pconfig->j_axis = atoi(value);
    }
    else if( MATCH("others", "pixels_i") )
    {
	pconfig->pixels_i = atoi(value);
    }
    else if( MATCH("others", "pixels_j") )
    {
	pconfig->pixels_j = atoi(value);
    }
    else if( MATCH("others", "tsettle") )
    {
	pconfig->tsettle = atoi(value);
    }
    else
    {
	return 0;
    }

    return 1;
}
