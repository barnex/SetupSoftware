#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H
#include <QtCore/qthread.h>
#include <QDebug>
#include <QMutex>
#include <QTimer>
 #include <QTcpSocket>
 #include <QIODevice>

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "myIO.h"

#include "../Libraries/errors.h"

class updateThread : public QThread
{
    Q_OBJECT
public:
    int sockfd;
    QTcpSocket *controller;
    int initSocket(int portno);
    int closeSocket();
signals:
    void sendValues(float *values);
private:
    void run();
private slots:
    void timerHit();
};


#endif // UPDATETHREAD_H
