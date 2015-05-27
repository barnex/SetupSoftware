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

// accept connection on listening socket, and return connection socket,
// with error checking.
int eaccept(int listener);

// listen on portno and return socket FD.
int initServer(int portno) __attribute__((warn_unused_result));

// connect to portno and return socket FD.
int initClient(int portno ) __attribute__((warn_unused_result));

#endif
