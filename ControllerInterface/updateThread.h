#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H
#include <QtCore/qthread.h>
#include <QDebug>
#include <QTimer>

class updateThread : public QThread
{
    Q_OBJECT

signals:
    void sendValues(double *values);
private:
    void run();
private slots:
    void timerHit();
};


#endif // UPDATETHREAD_H
