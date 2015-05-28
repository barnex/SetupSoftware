#! /bin/bash
set -e
set -v

gcc -c -std=c99 -Wall -Werror -O0 -g *.c
libs="/usr/lib64/librfftw.a /usr/lib64/libfftw.a /usr/lib/libportaudio.a -lasound"
gcc -lm *.o ../Libraries/*.o $libs -o FFTGrabber
