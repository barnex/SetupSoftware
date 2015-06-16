#! /bin/bash
set -e
set -v

gcc -c -std=c99 -Wall -Werror -O0 -g *.c
libs=""
gcc -lm *.o ../Libraries/*.o $libs -o HPInterface
