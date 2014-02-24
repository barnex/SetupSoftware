#ifndef MYIO_H
#define MYIO_H

#include <QTcpSocket>
#include <QIODevice>

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "../Libraries/errors.h"

int myReadfull(QTcpSocket * socket, void *buffer, int nbytes );

#endif // MYIO_H
