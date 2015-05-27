#include "socket.h"
#include "io.h"

void checkPort(int portno) {
	if(portno == 0) {
		fatal("port 0 not allowed");
	}
}

int eaccept(int listener){
	int sock = accept(listener, 0, 0);
	if(sock < 0){
		fatal("accept");
	}
	printf("accepted connection, fd=%x\n", sock);
	return sock;
}

int initServer(int portno ) {
	int sockfd;

	fprintf(stderr, "%s: init server, port %d\n", progname, portno);
	checkPort(portno);

	struct sockaddr_in serv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fatal("init server");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	         sizeof(serv_addr)) < 0) {
		fatal("init server (bind)");

	}
	listen(sockfd,5);
	return sockfd;
}

int initClient(int portno) {
	fprintf(stderr, "%s: init client, port %d\n", progname, portno);
	checkPort(portno);

	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fatal("init client");
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
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		fatal("init client (connect)");
	}
	return sockfd;
}

int initRemoteClient(char *hostname, int portno ) {
	fprintf(stderr, "%s: init remote client, %s:%d\n", progname, hostname, portno);
	checkPort(portno);

	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fatal("init remote client (socket)");
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
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		fatal("init remote client (connect)");
	}
	return sockfd;
}
