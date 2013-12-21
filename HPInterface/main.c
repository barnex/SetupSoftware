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

static void catchkill(int signal)
{
    fprintf(logfile, "Program has been killed by signal %d\n", signal);
    printf("I have been killed!\n");
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
	 * This opens a socket the the GPIB/HPIB interface from Prologix at ip 192.168.103:1234
	 */
	int gpibsockfd = 0;
	struct sockaddr_in gpib_addr;
	gpibsockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset( &gpib_addr, 0, sizeof(gpib_addr) );
	gpib_addr.sin_family = AF_INET;
	gpib_addr.sin_port = htons(1234);
	inet_pton(AF_INET, "192.168.0.103", &gpib_addr.sin_addr);
	connect( gpibsockfd, (struct sockaddr *)&gpib_addr, sizeof(gpib_addr));

	memset(buffer, 0, 256);
	sprintf(buffer, "++mode 1\n");
	write(gpibsockfd, buffer, 256);
	sprintf(buffer, "++auto 1\n");
	write(gpibsockfd, buffer, 256);
	sprintf(buffer, "++addr 1\n");
	write(gpibsockfd, buffer, 256);
	
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
			int retval = -1;
			if ( strlen(buffer) > 2 )
			{	 
			    fprintf(logfile, "Incoming: %s", buffer );
			    printf("Incoming: %s", buffer );
			    float freq = atof(strtok(buffer, ","));
			    
			    int ok = 1;
			    if( freq < 6.2e9 )
			    {
				ok = 0;
			    }
			    else if( freq < 12.4e9 )
			    {
				ok = ((int) (freq/1.0e3)) % 2;

			    } 
			    else 
			    {
				ok = ((int) (freq/1.0e3)) % 3;
			    }
			   
			    if( !ok )
			    { 

				int ghz = (int)(freq/1.0e9);
				int mhz = (freq - (float)ghz*1.0e9)/1.0e6;
				int khz = (freq - (float)ghz*1.0e9 - (float)mhz*1.0e6) / 1.0e3;

				if( ghz >= 10 )
				{
				    memset(buffer, 0, 256);
				    sprintf(buffer, "P%d%dT%d%dZ1\n", ghz, mhz/10, mhz % 10, khz);
				    printf("%s\t", buffer);
				    write(gpibsockfd, buffer, 256);
				}
				else
				{
				    memset(buffer, 0, 256);
				    sprintf(buffer, "Q%d%dT%d%dZ1\n", ghz, mhz/10, mhz % 10, khz);
				    printf("%s\t", buffer);
				    write(gpibsockfd, buffer, 256);
				}
				retval = 0;
			    
				char buff[64];
				bzero(buff, 64);
				sprintf(buff, "%d\n", retval);
				write(newsockfd, &buff, sizeof(buff));
			    }
			    else
			    {
				retval = -1;
			    
				char buff[64];
				bzero(buff, 64);
				sprintf(buff, "%d\n", retval);
				write(newsockfd, &buff, sizeof(buff));

			    }
			    
			    memset(buffer, 0, 256);
			    ret = read(newsockfd, buffer, 256);
			}
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
	close(gpibsockfd);
    }
    else
    {
	fprintf(stdout, "Usage: LOInterface [accepted client] [portno]\n");
	fflush(logfile);
	fclose(logfile);
	return EXIT_SUCCESS;
    }
}
