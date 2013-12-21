#ifndef _PEAKFIND_H
#define _PEAKFIND_H

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

int getValue(int monaSock, double bandwidth, double *avgNoise, double *stdNoise, double *peakValue, double fCenter);

#endif
