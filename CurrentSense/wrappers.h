#ifndef _WRAPPERS_H
#define _WRAPPERS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Libraries/io.h"
#include "mydefs.h"
#include "errors.h"

int measureWrapper  (int *sockfd, int *usbfd);
int idWrapper	    (int *sockfd);

#endif
