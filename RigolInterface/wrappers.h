#ifndef _WRAPPERS_H
#define _WRAPPERS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Libraries/io.h"
#include "../Libraries/mydefs.h"
#include "../Libraries/errors.h"

int measureWrapper  (int *sockfd, FILE *usbfd);
int idWrapper	    (int *sockfd);

#endif
