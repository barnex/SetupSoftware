#include "controller.h"

Controller::Controller(void)
{
    controller = new QTcpSocket();
    lock = new QMutex();

    status = CONTROLLER_IDLE;
}

Controller::~Controller()
{
    controller->close();
    free(controller);
    free(lock);
}

int Controller::init(int portno)
{
    controller->connectToHost("localhost", portno, QIODevice::ReadWrite);
    // Request the current position of the piezo and set as current position
    memset(currentPosition, 0, sizeof(float)*4);
    getPosition( currentPosition );
    //qDebug() << currentPosition[0] << currentPosition[1] << currentPosition[2];
    // Set this as the start position
    memmove( startPosition, currentPosition, sizeof(float)*4);
    char cmdString[1024];
    int32_t dmp[2];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "SET,START,%f,%f,%f,%f\n", startPosition[0], startPosition[1], startPosition[2], startPosition[3]);
    controller->write(cmdString, strlen(cmdString));
    myReadfull(dmp, sizeof(int32_t)*2);

    // set all other values to zero and let the controller know
    memset(IInc, 0, sizeof(float)*4);
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,IINC,0.0,0.0,0.0,0.0\n");
    controller->write(cmdString, strlen(cmdString));
    myReadfull(dmp, sizeof(int32_t)*2);

    memset(JInc, 0, sizeof(float)*4);
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,JINC,0.0,0.0,0.0,0.0\n");
    controller->write(cmdString, strlen(cmdString));
    myReadfull(dmp, sizeof(int32_t)*2);

    pixels = 0;
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,PIXELS,0.0\n");
    controller->write(cmdString, strlen(cmdString));
    myReadfull(dmp, sizeof(int32_t)*2);

    t_settle = 2;
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,TSETTLE,2.0\n");
    controller->write(cmdString, strlen(cmdString));
    myReadfull(dmp, sizeof(int32_t)*2);

    return SUCCESS;
}

int Controller::myReadfull(void *buffer, int nbytes )
{
    memset( buffer, 0, nbytes );
    char *buffercast = (char *) buffer;
    int bytesread = 0;
    bytesread = controller->read(buffercast, nbytes);
    while( bytesread < nbytes && bytesread >= 0 )
    {
        bytesread += controller->read(&(buffercast[bytesread]), nbytes - bytesread);
    }
    return bytesread;
}

int Controller::getPosition( float *pos )
{
    lock->lock();
    status = CONTROLLER_BUSY;
    int32_t bufferIn[2] = {0, 0};
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "GET,POSITION\n");

    controller->write(cmdString, strlen(cmdString));
    myReadfull((void*) bufferIn, sizeof(int32_t)*2);
    if(bufferIn[0] == SUCCESS)
    {
        myReadfull((void*) pos, sizeof(float)*4);
        qDebug() << pos[0] << pos[1] << pos[2];
        status = CONTROLLER_IDLE;
        lock->unlock();
        return SUCCESS;
    }
    else
    {
        lock->unlock();
        status = CONTROLLER_IDLE;
        return -1;
    }
}

int Controller::setPosition(float * pos)
{
    lock->lock();
    char cmdString[1024];
    int32_t dmp[2];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "SET,START,%f,%f,%f,%f\n", pos[0], pos[1], pos[2], pos[3]);
    controller->write(cmdString, strlen(cmdString));
    myReadfull(dmp, sizeof(int32_t)*2);
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "GOTO\n");
    controller->write(cmdString, strlen(cmdString));
    myReadfull(dmp, sizeof(int32_t)*2);
    lock->unlock();
    return 1;
}
