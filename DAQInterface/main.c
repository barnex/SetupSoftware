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

#include "GPIO.h"
#include "DAC.h"

FILE * logfile;
DAC_struct myDAC;

static void catchkill(int signal)
{
    fprintf(logfile, "Program has been killed by signal %d\n", signal);
    printf("I have been killed!\n");
    fflush(logfile);
    fclose(logfile);
    raise(SIGKILL);
}
void handleRequest(char * command, int channel, float value, char * buffer)
{
    if( strncmp(command, "SET", 3) == 0 )
    {
        int ret = setDAC(&myDAC, channel, (double) value);
        sprintf(buffer, "%d\n", ret);
    }
    else if( strncmp(command, "MEAS", 4) == 0 )
    {
        sprintf(buffer, "Hold on, not yet implemented\n");
    }
    else
    {
        sprintf(buffer, "Unknown command\n");
    }
}

int main(int argc, char **argv)
{
    signal(SIGTERM, catchkill);
    if( argc >= 3 )
    {
	logfile = fopen("/var/log/DAQinterface.log", "a+");
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

    setup_io();

    initDAC( 22, 0, &myDAC );

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
		    printf("Accepted new connection from %s\n", client_name);
		    bzero(buffer,256);
		    int ret = read(newsockfd,buffer,256);
		    while( ret > 0 && (strpbrk(buffer, "STOP") == strpbrk("a", "b") ) )
		    {
			    if ( strlen(buffer) > 2 )
			    {	 
			        fprintf(logfile, "Incoming: %s", buffer );
			        printf("Incoming: %s", buffer );
			        char *command = (strtok(buffer, ","));
			        int channel = atoi(strtok(NULL, ","));
                    float value = 0.0;
                    if( strncmp(command, "SET", 3) == 0 )
                    {
			            value = atof(strtok(NULL, ","));
                    }

			        bzero(buffer, 256);

                    handleRequest(command, channel, value, buffer);
			        write(newsockfd, buffer, sizeof(buffer));

                    bzero(buffer, 256);

			        ret = read(newsockfd, buffer, 256);
			    }

		        close(newsockfd);
		        fprintf(logfile, "Disconnected from client\n");
		        fflush(logfile);
		    }
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
