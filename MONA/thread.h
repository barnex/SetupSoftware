#ifndef _THREAD_H
#define _THREAD_H

#include "mona.h"
#include <complex.h>
#include <rfftw.h>

void* dataCopyThread(void* args);
void* FFTThread(void *args);

#endif
