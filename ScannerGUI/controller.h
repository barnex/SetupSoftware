#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTcpSocket>
#include <QIODevice>
#include "../Libraries/errors.h"
#include <QDebug>

#define CONTROLLER_BUSY    1
#define CONTROLLER_IDLE    2

class Controller
{
private:
    QTcpSocket *controller;
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
    int getStatus();
    int singleMeasurement(float *results);
    // Basic getters
    int getStartPosition(float *pos);
    int getCurrentPosition (float *pos);
    int getIInc(float *iinc);
    int getJInc(float *jinc);
    int getPixels(int *pixels);
    int getTSettle(int *t_settle);
    // and setters
    int setStartPosition( float *pos );
    int setCurrentPosition (float *pos);
    int setIInc(float *iinc);
    int setJInc(float *jinc);
    int setPixels(int *pixels);
    int setTSettle(int *t_settle);
};

#endif // CONTROLLER_H
