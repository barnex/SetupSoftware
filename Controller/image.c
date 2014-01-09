#include "image.h"
int createImage( FILE * target, uint16_t *pixelArray, int pixels )
{
    MagickWand *magick_wand;
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    MagickConstituteImage(  magick_wand, 
			    (const unsigned long)pixels, 
			    (const unsigned long)pixels,
			    "I",
			    ShortPixel,
			    pixelArray
			);
    MagickWriteImage(magick_wand, "test.bmp");
    DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return 0;
}
