#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H
#include <QtCore/qthread.h>
#include <QDebug>
#include <QMutex>
#include <QTimer>

class updateThread : public QThread
{
    Q_OBJECT
public:
    int *sockfd;
    QMutex *mutex;
signals:
    void sendValues(double *values);
private:
    void run();
private slots:
    void timerHit();
};


#endif // UPDATETHREAD_H
