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
    int32_t bufferIn[2] = {0, 0};

    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "MEAS\n");

    controller->write(cmdString, strlen(cmdString));
    myReadfull(controller, (void*) bufferIn, sizeof(int32_t)*2);

    if( bufferIn[0] == SUCCESS)
    {
        float values[8];
        myReadfull(controller, (void *)values, sizeof(float)*8);
        emit sendValues(values);
    }
}

int updateThread::initSocket(int portno)
{
    controller = new QTcpSocket();
    controller->connectToHost("localhost", portno, QIODevice::ReadWrite);
    return 1;
}

int updateThread::closeSocket()
{
    controller->disconnectFromHost();
    return 1;
}
