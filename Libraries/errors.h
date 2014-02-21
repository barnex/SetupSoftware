#ifndef _ERRORS_H
#define _ERRORS_H

#include <stdint.h>

/*
 * This file contains the definitions of the error codes returned by
 * the servers. (Socket level)
 */

#define SUCCESS			(int32_t) 1
#define FINISHED		(int32_t) 2

#define UNKNOWN_COMMAND		(int32_t) -1
#define NOT_ENOUGH_PARAMETERS	(int32_t) -2
#define HARDWARE_COMM_ERR	(int32_t) -3
#define UNKNOWN_PARAMETER	(int32_t) -4

#endif
