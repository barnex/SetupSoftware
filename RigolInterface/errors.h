#ifndef _ERRORS_H
#define _ERRORS_H

#include <stdint.h>


#define SUCCESS			(int32_t) 1

#define UNKNOWN_COMMAND		(int32_t) -1
#define NOT_ENOUGH_PARAMETERS	(int32_t) -2
#define HARDWARE_COMM_ERR	(int32_t) -3
#define UNKNOWN_PARAMETER	(int32_t) -4

#endif
