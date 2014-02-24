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

void updateThread::setController(Controller * ctrlr)
{
    controller = ctrlr;
}

void updateThread::timerHit()
{
    float values[8];

    if( controller->getStatus() != CONTROLLER_BUSY )
    {
        controller->singleMeasurement(values);
        emit sendValues(values);
    }
}
