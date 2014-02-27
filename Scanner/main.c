#include "../Libraries/socket.h"
#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include "ini.h"
#include <signal.h>
#include <assert.h>

typedef struct
{
    float start[4];
    float scanx[4];
    float scany[4];
    int pixels;
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
    else if( MATCH("scanx", "x") )
    {
        pconfig->scanx[0] = atof(value);
    }
    else if( MATCH("scanx", "y") )
    {
        pconfig->scanx[1] = atof(value);
    }
    else if( MATCH("scanx", "z") )
    {
        pconfig->scanx[2] = atof(value);
    }
    else if( MATCH("scanx", "aux") )
    {
        pconfig->scanx[3] = atof(value);
    }

    else if( MATCH("scany", "x") )
    {
        pconfig->scany[0] = atof(value);
    }
    else if( MATCH("scany", "y") )
    {
        pconfig->scany[1] = atof(value);
    }
    else if( MATCH("scany", "z") )
    {
        pconfig->scany[2] = atof(value);
    }
    else if( MATCH("scany", "aux") )
    {
        pconfig->scany[3] = atof(value);
    }
    else if( MATCH("others", "pixels") )
    {
	pconfig->pixels = atoi(value);
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

    write( sockfd, cmdString, strlen(cmdString) );

    while( ( i < cfg->pixels * cfg->pixels ) && enabled )
    {
	memset(socketBuffer, 0, 2*sizeof(int32_t));
	ret = myReadfull(sockfd, (void *)socketBuffer, 2*sizeof(int32_t));
	if( socketBuffer[0] == SUCCESS )
	{
	    memset(floatBuffer, 0, 8*sizeof(float));
	    ret = myReadfull(sockfd, (void *)floatBuffer, 8*sizeof(float));
	    fprintf(destination, "%d\t%d", scan_i, scan_j);
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
	if( scan_i == cfg->pixels )
	{
	    direction *= -1;
	    scan_i += direction;
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
    myWrite( sockfd, "SET,IINC,%f,%f,%f,%f\n", cfg->scanx[0], cfg->scanx[1], cfg->scanx[2], cfg->scanx[3]);
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    // Set scany
    myWrite( sockfd, "SET,JINC,%f,%f,%f,%f\n", cfg->scany[0], cfg->scany[1], cfg->scany[2], cfg->scany[3]);
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    // Set pixels
    myWrite( sockfd, "SET,PIXELS,%f\n", (float)cfg->pixels );
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    // Set settle time
    myWrite( sockfd, "SET,TSETTLE,%f\n", (float)cfg->tsettle );
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
    myWrite( sockfd, "GOTO\n");
    myReadfull( sockfd, dmp, sizeof(int32_t)*2);
}
