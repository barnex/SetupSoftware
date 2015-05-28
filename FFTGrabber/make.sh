#! /bin/bash
set -e
set -v

gcc -c -std=c99 -Wall -Werror -O0 -g *.c

#libs for static linking
static="/usr/lib64/librfftw.a /usr/lib64/libfftw.a /usr/lib/libportaudio.a -lasound"

#libs for dynamic linking
dynamic="-lrfftw -lfftw -lportaudio"

# try static linking first, fallback to dynamic
gcc -lm *.o ../Libraries/*.o $static -o FFTGrabber 2> /dev/null || gcc *.o ../Libraries/*.o $dynamic -lpthread -lm -lrt -ldl -o FFTGrabber
