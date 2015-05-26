#include "socket.h"

int initServer( int *sockfd, int portno ) {
	struct sockaddr_in serv_addr;

	*sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (*sockfd < 0) {
		fprintf(stderr, "! ERROR: Could not open socket!\n");
		perror("! ERROR Message from system");
		return EXIT_FAILURE;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(*sockfd, (struct sockaddr *) &serv_addr,
	         sizeof(serv_addr)) < 0) {
		fprintf(stderr, "! ERROR: Could not open socket!\n");
		perror("! ERROR Message from system");
		return EXIT_FAILURE;

	}
	listen(*sockfd,5);
	return EXIT_SUCCESS;
}

int initClient( int *sockfd, int portno ) {
	struct sockaddr_in serv_addr;
	struct hostent *server;
	if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "! ERROR: Could not open socket!\n");
		perror("! ERROR Message from system");
		return EXIT_FAILURE;
	}

	server = gethostbyname("localhost");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = portno;

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr_list[0],
	      (char *)&serv_addr.sin_addr.s_addr,
	      server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(*sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		fprintf(stderr, "! ERROR: Could not open socket!\n");
		perror("! ERROR Message from system");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int initRemoteClient( int *sockfd, char *hostname, int portno ) {
	struct sockaddr_in serv_addr;
	struct hostent *server;
	if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "! ERROR: Could not open socket!\n");
		perror("! ERROR Message from system");
		return EXIT_FAILURE;
	}

	server = gethostbyname(hostname);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = portno;

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr_list[0],
	      (char *)&serv_addr.sin_addr.s_addr,
	      server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(*sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		fprintf(stderr, "! ERROR: Could not open socket!\n");
		perror("! ERROR Message from system");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
