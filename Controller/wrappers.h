#ifndef _WRAPPERS_H
#define _WRAPPERS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mydefs.h"
#include "errors.h"

#define UINT16_TO_FLOAT	1.52587890625e-5
#define INT16_TO_FLOAT	3.0517578125e-5

int setWrapper	    (char *stringParam, float *parameters, int *sockfd, int *usbfd);
int scan1DWrapper   (int *sockfd, int *usbfd);
int scan2DWrapper   (int *sockfd, int *usbfd);
int resetWrapper    (int *sockfd, int *usbfd);
int abortWrapper    (int *sockfd, int *usbfd);
int measureWrapper  (int *sockfd, int *usbfd);

#endif