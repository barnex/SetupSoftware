#ifndef _SETFREQS_H
#define _SETFREQS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

int setLTC(double LO1_value, double LO2_value, int sockfd);

int setHittite(double value, int sockfd);
int setHittitePwr(double value, int on, int sockfd);

int setHP(double value, int sockfd);

#endif
