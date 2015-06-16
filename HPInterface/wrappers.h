#ifndef _WRAPPERS_H
#define _WRAPPERS_H

#include "../Libraries/io.h"
#include "../Libraries/errors.h"
#include "../Libraries/socket.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int setWrapper( char *stringParam, double *value, int *sockfd, int gpib);
int idWrapper( int *sockfd );

#endif
