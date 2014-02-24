#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H
#include <QtCore/qthread.h>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include "controller.h"

class updateThread : public QThread
{
    Q_OBJECT
public:
    void setController(Controller *);
signals:
    void sendValues(float *values);
private:
    Controller *controller;
    void run();
private slots:
    void timerHit();
};


#endif // UPDATETHREAD_H
