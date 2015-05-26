#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTcpSocket>
#include <QIODevice>
#include <QMutex>
#include "../Libraries/errors.h"
#include <QDebug>
#include <QHostAddress>

#include <assert.h>
#include <unistd.h>

#include "socket.h"
#include "io.h"

#define CONTROLLER_BUSY    1
#define CONTROLLER_IDLE    2

class Controller {
private:
	int sockfd;
	int     t_settle;
public:
	Controller();
	~Controller();
	int init(int portno);
	// Basic getters
	int setPosition(float *pos);
	int getPosition (float *pos);
	int abort();
};

#endif // CONTROLLER_H
