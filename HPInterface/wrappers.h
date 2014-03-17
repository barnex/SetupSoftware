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

#include "gpib.h"
int setWrapper( char *stringParam, double *value, int *sockfd, gpibio *gpib);

int	idWrapper( int *sockfd );

#endif
