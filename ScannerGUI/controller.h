#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTcpSocket>
#include <QIODevice>
#include <QMutex>
#include "../Libraries/errors.h"
#include <QDebug>

#define CONTROLLER_BUSY    1
#define CONTROLLER_IDLE    2

class Controller {
private:
	QTcpSocket *controller;
	QMutex *lock;
	int     status;
	float   startPosition[4];
	float   currentPosition[4];
	float   IInc[4];
	float   JInc[4];
	int     pixels;
	int     t_settle;
	int myReadfull(void *, int );
public:
	Controller();
	~Controller();
	int init(int portno);
	// Basic getters
	int setPosition(float *pos);
	int getPosition (float *pos);
};

#endif // CONTROLLER_H
