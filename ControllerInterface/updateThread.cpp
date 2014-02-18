#include "updateThread.h"

void updateThread::run()
{
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer.setInterval(100);
    timer.start();
    exec();
    timer.stop();
}

void updateThread::timerHit()
{
    mutex->lock();
    if(sockfd > 0)
    {


    }

    mutex->unlock();
     double values[8];
     for(int i = 0; i < 8; i++)
     {
         values[i] = 10.5*(double)i;
     }
     emit sendValues(values);
}
