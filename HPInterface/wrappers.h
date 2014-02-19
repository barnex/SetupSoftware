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

#ifdef _USE_ARDUINO
#include "gpib.h"
int setWrapper( char *stringParam, float value, int *sockfd, gpibio *gpib);
#else
#ifdef _USE_PROLOGIX
int setWrapper( char *stringParam, float value, int *sockfd, int *gpibsock );
#endif
#endif

int	idWrapper( int *sockfd );

#endif
