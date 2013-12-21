#include <stdio.h>
#include <stdlib.h>
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

FILE * logfile;
FILE *hittite;

static void catchkill(int signal)
{
    fprintf(logfile, "Program has been killed by signal %d\n", signal);
    printf("I have been killed!\n");
    fflush(logfile);
    fclose(logfile);
    fflush(hittite);
    fclose(hittite);
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
	char buffer[128];
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
	 * This part initializes the Hittite
	 */
        hittite = fopen("/dev/hittite", "r+");
	int ret = 0;
	if( ret == -1 )
	{
	    fprintf(stderr, "! ERROR: Could not open a handle to the device\n");
	    perror("! ERROR Message from system");
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
		    printf("Accepted new connection from %s\n", client_name);
		    bzero(buffer,128);
		    ret = read(newsockfd,buffer,128);
		    while( ret > 0 && ( strpbrk( buffer, "STOP") == strpbrk("a", "b") ) )
		    {
			if ( strlen(buffer) > 2 )
			{	 
			    fprintf(logfile, "Incoming: %s", buffer );
			    printf("Incoming: %s", buffer );
			    fprintf(hittite,"%s", buffer);
			    bzero(buffer, 128);
			}
			write(newsockfd, buffer, 64);
			ret = read(newsockfd, buffer, 128);
		    }

		    close(newsockfd);
		    fprintf(logfile, "Disconnected from client\n");
		    printf("Disconnected from client\n");
		    fflush(logfile);
		}
		else
		{
		    char buff[128] = "You are not allowed to make a connection, fuck off\n";
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
