#ifndef _WRAPPERS_H
#define _WRAPPERS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <rfftw.h>
#include <assert.h>

#include "portaudio.h"

#include "../Libraries/mydefs.h"
#include "../Libraries/errors.h"
#include "../Libraries/io.h"

#include "main.h"

#define UINT16_TO_FLOAT	1.52587890625e-5
#define INT16_TO_FLOAT	3.0517578125e-5

int measureWrapper  (float *parameters, int *sockfd, handleData *args);
int idWrapper	    (int *sockfd);

#endif
