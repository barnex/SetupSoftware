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

typedef struct {
	float start[4];
	float width_i;
	float width_j;
	int i_axis;
	int j_axis;
	int pixels_i;
	int pixels_j;
	int tsettle;
	char savedir[1024];
	int socket;
} configuration;

int sockfd;

void catchSigint(int signum) {
	printf("Caught signal. Aborting scan...\n");
	char cmdString[] = "ABORT\n";
	ewrite( sockfd, cmdString, strlen(cmdString) );
	printf("Aborted scan.\n");
}

static int handler(void *user, const char *section, const char *name,
                   const char *value);


void init( configuration *cfg );

void scan2D( FILE *destination, configuration *cfg );

int main(int argc, char **argv) {
	configuration config;
	memset(&config, 0, sizeof(configuration));
	char *homeDir = getenv("HOME");
	assert(homeDir);
	char cfgfile[1024];
	memset(cfgfile, 0, 1024);
	sprintf(cfgfile, "%s/piezo_scanner.ini", homeDir );

	ini_parse(cfgfile, handler, &config);

	assert( signal( SIGINT, catchSigint ) != SIG_ERR );
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
	if(d) {
		while((dir = readdir(d)) != NULL) {
			if ( sscanf(dir->d_name, pattern, &tmp) > 0 ) {
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

	fprintf(dest, "#start %f, %f, %f, %f um^4\n", config.start[0], config.start[1], config.start[2], config.start[3]);
	fprintf(dest, "#width_i %f um, width_j %f um, pixels_i %d, pixels_j %d, tsettle %d\n", config.width_i,
	        config.width_j, config.pixels_i, config.pixels_j, config.tsettle);
	fprintf(dest, "#i axis %d, j axis %d\n", config.i_axis, config.j_axis);



	sockfd = initClient(5000); // TODO: port??
	init( &config );
	scan2D( dest, &config );
	close( sockfd );
	fclose(dest);
	return EXIT_SUCCESS;
}

static int handler(void *user, const char *section, const char *name,
                   const char *value) {
	configuration *pconfig = (configuration *)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if( MATCH("start", "x") ) {
		pconfig->start[0] = atof(value);
	} else if( MATCH("start", "y") ) {
		pconfig->start[1] = atof(value);
	} else if( MATCH("start", "z") ) {
		pconfig->start[2] = atof(value);
	} else if( MATCH("start", "aux") ) {
		pconfig->start[3] = atof(value);
	} else if( MATCH("scan", "width_i") ) {
		pconfig->width_i = atof(value);
	} else if( MATCH("scan", "width_j") ) {
		pconfig->width_j = atof(value);
	} else if( MATCH("scan", "i_axis") ) {
		pconfig->i_axis = atoi(value);
	} else if( MATCH("scan", "j_axis") ) {
		pconfig->j_axis = atoi(value);
	} else if( MATCH("others", "pixels_i") ) {
		pconfig->pixels_i = atoi(value);
	} else if( MATCH("others", "pixels_j") ) {
		pconfig->pixels_j = atoi(value);
	} else if( MATCH("others", "tsettle") ) {
		pconfig->tsettle = atoi(value);
	} else if( MATCH("others", "socket") ) {
		pconfig->socket = atoi(value);
	} else if( MATCH("others", "save_dir") ) {
		memmove(pconfig->savedir, value, strlen(value));
	} else {
		return 0;
	}
	return 1;
}

void scan2D( FILE *destination, configuration *cfg ) {
	char cmdString[] = "SCAN_2D\n";
	//int ret = 0;
	int i = 0;
	int enabled = 1;
	int32_t socketBuffer[2] = {0, 0};
	float floatBuffer[8];
	int scan_i = 0, scan_j = 0, direction = 1;
	float iinc = cfg->width_i / (float)cfg->pixels_i;
	float jinc = cfg->width_j / (float)cfg->pixels_j;

	ewrite( sockfd, cmdString, strlen(cmdString) );

	while( ( i < cfg->pixels_i * cfg->pixels_j ) && enabled ) {
		memset(socketBuffer, 0, 2*sizeof(int32_t));
		myReadfull(sockfd, (void *)socketBuffer, 2*sizeof(int32_t));
		if( socketBuffer[0] == SUCCESS ) {
			memset(floatBuffer, 0, 8*sizeof(float));
			myReadfull(sockfd, (void *)floatBuffer, 8*sizeof(float));
			fprintf(destination, "%f\t%f",  cfg->start[cfg->i_axis] + iinc*(float)scan_i,
			        cfg->start[cfg->j_axis] + jinc*(float)scan_j);
			for(int j = 0; j < 100; j++) {
				fprintf(stdout, " ");
			}
			fprintf(stdout, "\r");
			fprintf(stdout, "%f\t%f",  cfg->start[cfg->i_axis] + iinc*(float)scan_i,
			        cfg->start[cfg->j_axis] + jinc*(float)scan_j);
			for(int j = 0; j < 8; j++ ) {
				fprintf(destination, "\t%e", floatBuffer[j]);
				fprintf(stdout, "\t%e", floatBuffer[j]);
			}
			fprintf(destination, "\n");
			fprintf(stdout, "\r");
			fflush(destination);
		} else {
			return;
		}
		i++;
		scan_i += direction;
		if( scan_i == cfg->pixels_i || scan_i < 0 ) {
			//direction *= -1;
			//scan_i += direction;
			scan_i = 0;
			scan_j++;
		}
	}

}

void init(configuration *cfg) {
	int32_t dmp[2] = {0, 0};
	// Set start
	myWrite( sockfd, "SET,START,%f,%f,%f,%f\n", cfg->start[0]/20.0, cfg->start[1]/20.0, cfg->start[2]/20.0, cfg->start[3]/20.0);
	myReadfull( sockfd, dmp, sizeof(int32_t)*2);
	// Set scanx
	float scani[4] = {0.0, 0.0, 0.0, 0.0};
	scani[cfg->i_axis] = cfg->width_i /(20.0 * (float) cfg->pixels_i);
	myWrite( sockfd, "SET,IINC,%f,%f,%f,%f\n", scani[0], scani[1], scani[2], scani[3]);
	myReadfull( sockfd, dmp, sizeof(int32_t)*2);
	// Set scany
	float scanj[4] = {0.0, 0.0, 0.0, 0.0};
	scanj[cfg->j_axis] = cfg->width_j / (20.0 * (float) cfg->pixels_j);
	myWrite( sockfd, "SET,JINC,%f,%f,%f,%f\n", scanj[0], scanj[1], scanj[2], scanj[3]);
	myReadfull( sockfd, dmp, sizeof(int32_t)*2);
	// Set pixels
	myWrite( sockfd, "SET,PIXELS,%f,%f\n", (float)cfg->pixels_i, (float)cfg->pixels_j );
	myReadfull( sockfd, dmp, sizeof(int32_t)*2);
	// Set settle time
	myWrite( sockfd, "SET,TSETTLE,%f\n", (float)cfg->tsettle );
	myReadfull( sockfd, dmp, sizeof(int32_t)*2);
	myWrite( sockfd, "GOTO\n");
	myReadfull( sockfd, dmp, sizeof(int32_t)*2);
}
