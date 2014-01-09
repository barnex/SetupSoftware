#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
#include <stdio.h>
#include <wand/MagickWand.h>

int createImage( FILE * target, uint16_t *pixelArray, int pixels );

#endif
