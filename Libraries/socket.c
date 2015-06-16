#include "socket.h"
#include "io.h"

void checkPort(int portno) {
	if(portno == 0) {
		fatal("port 0 not allowed");
	}
}

int eaccept(int listener) {
	printf("%s: listening for connections...\n", progname);
	int sock = accept(listener, 0, 0);
	if(sock < 0) {
		fatal("accept");
	}
	printf("%s: accepted connection\n", progname);
	return sock;
}

int esocket() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fatal("opening socket");
	}
	return sockfd;
}

// TODO: pass port as string, atoi here!
int initServer(int portno) {

	fprintf(stderr, "%s: serving at port %d\n", progname, portno);
	checkPort(portno);

	int sockfd = esocket();

	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	         sizeof(serv_addr)) < 0) {
		fatal("bind");

	}
	listen(sockfd,5);
	return sockfd;
}

int connect_to(char *hostname, int portno) {
	fprintf(stderr, "%s: connecting to %s:%d\n", progname, hostname, portno);
	checkPort(portno);

	int sockfd = esocket();

	struct sockaddr_in serv_addr;
	struct hostent *server;

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
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		fatal("connect");
	}
	return sockfd;
}

int initClient(int portno) {
	return connect_to("localhost", portno);
}

