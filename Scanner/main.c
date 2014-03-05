#include "../Libraries/socket.h"
#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include "ini.h"
#include <signal.h>
#include <math.h>
#include <assert.h>

typedef struct
{
    float start[4];
    float width_x;
    float width_y;
    int x_axis;
    int y_axis;
    int pixels_x;
    int pixels_y;
    int tsettle;
} configuration;

int sockfd;

void catchSigint(int signum)
{
    printf("Caught signal. Aborting scan...\n");
    char cmdString[] = "ABORT\n";
    write( sockfd, cmdString, strlen(cmdString) );
    printf("Aborted scan.\n");
}

static int handler(void *user, const char *section, const char *name,
    const char *value);


void init( configuration *cfg );

void scan2D( FILE *destination, configuration *cfg );

int main(int argc, char **argv)
{
    configuration config;
    if( argc != 3 )
    {
	printf("Please specify config file and target file\n");
	return EXIT_FAILURE;
    }

    if( ini_parse(argv[1], handler, &config) )
    {
        printf("Could not load \"%s\" as config file\n", argv[1]);
	return EXIT_FAILURE;
    }

    assert( signal( SIGINT, catchSigint ) != SIG_ERR );;

    FILE * dest = fopen(argv[2], "w");

    FILE *configfile = fopen(argv[1], "r");
    char line[256];
    memset(line, 256, 0);
    while( fscanf( configfile, "%s", line ) > 0 )
    {
	fprintf(dest, "#%s\n", line );
	memset(line, 256, 0);
    }
	

    sockfd = 0;

    initClient( &sockfd, 5000);
    init( &config );
    scan2D( dest, &config );
    close( sockfd );
    fclose(dest);
    return EXIT_SUCCESS;
}

static int handler(void *user, const char *section, const char *name,
    const char *value)
{
    configuration *pconfig = (configuration *)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if( MATCH("start", "x") )
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
        pconfig->width_x = atof(value);
    }
    else if( MATCH("scan", "width_j") )
    {
        pconfig->width_y = atof(value);
    }
    else if( MATCH("scan", "i_axis") )
    {
        pconfig->x_axis = atoi(value);
    }
    else if( MATCH("scan", "j_axis") )
    {
        pconfig->y_axis = atoi(value);
    }
    else if( MATCH("others", "pixels_i") )
    {
	pconfig->pixels_x = atoi(value);
    }
    else if( MATCH("others", "pixels_j") )
    {
	pconfig->pixels_y = atoi(value);
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

void scan2D( FILE *destination, configuration *cfg )
{
    char cmdString[] = "SCAN_2D\n";
    int ret = 0, i = 0, enabled = 1;
    int32_t socketBuffer[2] = {0, 0};
    float floatBuffer[8];
    int scan_i = 0, scan_j = 0, direction = 1;
    float iinc = cfg->width_x / (float)cfg->pixels_x;
    float jinc = cfg->width_y / (float)cfg->pixels_y;

    write( sockfd, cmdString, strlen(cmdString) );

    while( ( i < cfg->pixels_x * cfg->pixels_y ) && enabled )
    {
	memset(socketBuffer, 0, 2*sizeof(int32_t));
	ret = myReadfull(sockfd, (void *)socketBuffer, 2*sizeof(int32_t));
	if( socketBuffer[0] == SUCCESS )
	{
	    memset(floatBuffer, 0, 8*sizeof(float));
	    ret = myReadfull(sockfd, (void *)floatBuffer, 8*sizeof(float));
	    fprintf(destination, "%f\t%f",  cfg->start[cfg->x_axis] + iinc*(float)scan_i,
					    cfg->start[cfg->y_axis] + jinc*(float)scan_j);
	    for(int j = 0; j < 8; j++ )
	    {
		fprintf(destination, "\t%e", floatBuffer[j]);
	    }
	    fprintf(destination, "\n");
	    fflush(destination);
	}
	else
	{
	    return;
	}
	i++;
	scan_i += direction;
	if( scan_i == cfg->pixels_x || scan_i < 0 )
	{
	    //direction *= -1;
	    //scan_i += direction;
	    scan_i = 0;
	    scan_j++;
	}
    }

}

void init(configuration *cfg)
{
    int32_t dmp[2] = {0, 0};
    // Set start
    myWrite( sockfd, "SET,START,%f,%f,%f,%f\n", cfg->start[0], cfg->start[1], cfg->start[2], cfg->start[3]);
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    // Set scanx
    float scanx[4] = {0.0, 0.0, 0.0, 0.0};
    scanx[cfg->x_axis] = cfg->width_x / (float) cfg->pixels_x;
    myWrite( sockfd, "SET,IINC,%f,%f,%f,%f\n", scanx[0], scanx[1], scanx[2], scanx[3]);
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    // Set scany
    float scany[4] = {0.0, 0.0, 0.0, 0.0};
    scany[cfg->y_axis] = cfg->width_y / (float) cfg->pixels_y;
    myWrite( sockfd, "SET,JINC,%f,%f,%f,%f\n", scany[0], scany[1], scany[2], scany[3]);
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    // Set pixels
    myWrite( sockfd, "SET,PIXELS,%f,%f\n", (float)cfg->pixels_x, (float)cfg->pixels_y );
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    // Set settle time
    myWrite( sockfd, "SET,TSETTLE,%f\n", (float)cfg->tsettle );
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    myWrite( sockfd, "GOTO\n");
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
}
