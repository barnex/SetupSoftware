#include "LOInterface.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <netdb.h>
#include <signal.h>

LOInterface *LO_High, *LO_Low;
FILE * logfile;

static void catchkill(int signal)
{
    fprintf(logfile, "Program has been killed by signal %d\n", signal);
    printf("I have been killed!\n");
    if( LO_High != NULL)
    {
	freeLO(LO_High);
    }
    if( LO_Low != NULL )
    {
	freeLO(LO_Low);
    }
    fflush(logfile);
    fclose(logfile);
    raise(SIGKILL);
}

int main(int argc, char **argv)
{
    signal(SIGTERM, catchkill);
    if( argc >= 3 )
    {
	logfile = fopen("/var/log/lointerface.log", "a+");
	printf("1\n");
	int portno = atoi(argv[2]);
        char *allowed_client = argv[1];
	/*
	 * This part initializes the socket
	 */
	/* Create a socket to listen to (act as server) */
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
	    fprintf(logfile, "! ERROR: Could not open socket\n");
	    fprintf(logfile, "!Error Message from system %s", strerror(errno));
	    fprintf(stderr, "! ERROR: Could not open socket!\n");
	    perror("! ERROR Message from system");
	    fflush(logfile);
	    fclose(logfile);
	    return EXIT_FAILURE;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	fprintf(logfile, "Port for binding is %d\n", portno);
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	    sizeof(serv_addr)) < 0)
	{
	    fprintf(logfile, "! ERROR: Could not open socket\n");
	    fprintf(logfile, "!Error Message from system %s", strerror(errno));
	    fprintf(stderr, "! ERROR: Could not open socket!\n");
	    perror("! ERROR Message from system");
	    fflush(logfile);
	    fclose(logfile);
	    return EXIT_FAILURE;

	}
	listen(sockfd,5);
	fprintf(logfile, "Succesfully opened socket, now listening\n");
	fflush(logfile);
	clilen = sizeof(cli_addr);

	/*
	 * This part initializes the PLL's
	 */
	LO_High = malloc(sizeof(LOInterface));
        int ret = initLO(LO_High, "/dev/spidev0.0");
	if( ret == -1 )
	{
	    fprintf(logfile, "! ERROR: Could not handle to device\n");
	    fprintf(logfile, "!Error Message from system %s", strerror(errno));
	    fprintf(stderr, "! ERROR: Could not open handle to device!\n");
	    perror("! ERROR Message from system");
	    fflush(logfile);
	    fclose(logfile);
	    return EXIT_FAILURE;
	}

	LO_Low = malloc(sizeof(LOInterface));
        ret = initLO(LO_Low, "/dev/spidev0.1");
	if( ret == -1 )
	{
	    fprintf(logfile, "! ERROR: Could not open handle to device\n");
	    fprintf(logfile, "!Error Message from system %s", strerror(errno));
	    fprintf(stderr, "! ERROR: Could not open handle to device!\n");
	    perror("! ERROR Message from system");
	    fflush(logfile);
	    fclose(logfile);
	    return EXIT_FAILURE;
	}

	fprintf(logfile, "Entering infinite loop...\n");
	/* Infinite loop */
	while(1)
	{
        /* Listen for incoming calls */
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		char client_ip[256];
		char client_name[256];
		char serv_name[256];
		struct sockaddr_in *tmp = (struct sockaddr_in *)&cli_addr;
		inet_ntop(AF_INET, &(tmp->sin_addr), client_ip, clilen);
		getnameinfo((struct sockaddr *) &cli_addr, clilen,
		    client_name, 256,  serv_name, 256, 0);
		if( strcmp(client_name, allowed_client) == 0 )
		{
		    fprintf(logfile, "Accepted new connection from %s\n", client_name);
		    bzero(buffer,256);
		    ret = read(newsockfd,buffer,256);
		    while( ret > 0 && (strpbrk(buffer, "STOP") == strpbrk("a", "b") ) )
		    {
			int retval = -1;
			if ( strlen(buffer) > 2 )
			{	 
			    fprintf(logfile, "Incoming: %s", buffer );
			    float freq1 = atof(strtok(buffer, ","));
			    float freq2 = atof(strtok(NULL, ","));
			    fprintf(logfile, "Frequency LO-0: %f MHz\n", freq1);
			    fprintf(logfile, "Frequency LO-1: %f MHz\n", freq2);
			    bzero(buffer, 256);
			    retval = -1;
			    
			    if( freq1 < 0.0 )
			    {
				fprintf(logfile, "Request to reset LO_High\n");
				freeLO(LO_High);
				ret = initLO(LO_High, "/dev/spidev0.0");
				if( ret == -1 )
				{
				    fprintf(logfile, "! ERROR: Could not open handle to device\n");
				    fprintf(logfile, "!Error Message from system %s", strerror(errno));
				    fprintf(stderr, "! ERROR: Could not open handle to device!\n");
				    perror("! ERROR Message from system");
				}
			    }
			    else
			    {
				if( freq1 > 0.0 )
				{
				    retval = setFrequency(freq1, LO_High);
				}
				if( freq2 > 0.0 )
				{
				    retval = setFrequency(freq2, LO_Low);
				}
			    }
			}
			    /*
			    else if( lo == 1 )
			    {
				if( frequency < 0.0 )
				{
				    fprintf(stdout, "Request to reset LO_Low\n");
				    freeLO(LO_Low);
				    retval = initLO(LO_Low, "/dev/spidev0.1");
				    if( retval == -1 )
				    {
					fprintf(logfile, "! ERROR: Could not open handle to device\n");
					fprintf(logfile, "!Error Message from system %s", strerror(errno));
					fprintf(stderr, "! ERROR: Could not open handle to device!\n");
					perror("! ERROR Message from system");
				    }
				}
				else if(frequency > 0.0 )
				{
				    retval = setFrequency(frequency, LO_Low);
				}
			    }
			    */
			    char buff[64];
			    bzero(buff, 64);
			    sprintf(buff, "%d\n", retval);
			    write(newsockfd, &buff, sizeof(buff));
			    ret = read(newsockfd, buffer, 256);
			}

		    close(newsockfd);
		    fprintf(logfile, "Disconnected from client\n");
		    fflush(logfile);
		}
		else
		{
		    char buff[256] = "You are not allowed to make a connection, fuck off\n";
		    write(newsockfd, buff, sizeof(buff));
		    close(newsockfd);
		    fprintf(logfile, "Unauthorized entry tried from %s\n", client_name);
		    fflush(logfile);
		}
	}
    }
    else
    {
	fprintf(stdout, "Usage: LOInterface [accepted client] [portno]\n");
	fflush(logfile);
	fclose(logfile);
	return EXIT_SUCCESS;
    }
}
