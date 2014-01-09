#ifndef _CONTROLLER_H
#define _CONTROLLER_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>

#include "mydefs.h"
#include "image.h"

int abortscan(int fd);

int setStart(int fd, int *start);
int setIInc(int fd, int *i_inc);
int setJInc(int fd, int *j_inc);
int setTSettle(int fd, int t_settle);
int setPixels(int fd, int pixels);

int getPosition(int fd, int *position);
int getChannels(int fd, int *values);

int gotoPosition(int fd, int *position);
int OneDScan(int fd, uint16_t *pixelList, int wait_time);
int TwoDScan(int fd, uint16_t *pixelList, const char *filename);

#endif
