#! /bin/bash
set -e

echo gcc -c -std=c99 -Wall -Werror -O0 -g *.c
gcc -c -std=c99 -Wall -Werror -O0 -g *.c

libs="/usr/lib64/librfftw.a /usr/lib64/libfftw.a /usr/lib/libportaudio.a -lasound"

echo gcc -lm *.o ../Libraries/*.o $libs -o FFTGrabber
gcc -lm *.o ../Libraries/*.o $libs -o FFTGrabber
