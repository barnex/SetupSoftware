#ifndef _IO_H
#define _IO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <strings.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <stdarg.h>
#include "errors.h"

// write with error checking.
void ewrite(int fd, const void *buf, size_t nbytes);

// fgets with error checking.
void efgets(char *str, int num, FILE *stream);

// abort with error message.
void fatal(char *msg);

// set the program name to be reported in errors
// typically in main: setProgName(argv[0]);
void setProgName(char *name);

int myReadfull( int fd, void *buffer, int nBytes );

int myRead( int fd, void *buffer, int nBytes );

int myWrite( int fd, const char *format, ...);

int initSerial( int *fd, int baudrate, char *devname );

#endif
