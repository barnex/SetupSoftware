#ifndef _SOCKET_H
#define _SOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <strings.h>
#include <string.h>
#include <netdb.h>
#include <assert.h>

int initServer( int *sockfd, int portno );
int initClient( int *sockfd, int portno );
int initRemoteClient( int *sockfd, char *hostname, int portno );

#endif
