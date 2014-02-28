#include "controller.h"

Controller::Controller(void)
{
    controller = new QTcpSocket();

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

    t_settle = 10;
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,TSETTLE,10.0\n");
    controller->write(cmdString, strlen(cmdString));
    controller->flush();
    int32_t dmp[2] = {0, 0};
    myReadfull(dmp, sizeof(int32_t)*2);
    qDebug() << dmp[0] << " and " << dmp[1];\
    int i = 0;
    while(1)
    {
    myReadfull(dmp, sizeof(int32_t)*2);
    qDebug() << i << " " << dmp[0] << " and " << dmp[1];
    i++;
    }
    myReadfull(dmp, sizeof(int32_t)*2);
    qDebug() << dmp[0] << " and " << dmp[1];
    usleep(100);

    return SUCCESS;
}

int Controller::abort()
{
    char cmdString[] = "ABORT\n";
    controller->write(cmdString, strlen(cmdString));
    controller->flush();
    int32_t dmp[2] = {0, 0};
    myReadfull(dmp, sizeof(int32_t)*2);
    return 1;
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
    status = CONTROLLER_BUSY;
    int32_t bufferIn[2] = {0, 0};
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "GET,POSITION\n");

    controller->write(cmdString, strlen(cmdString));\
    controller->flush();
    //myReadfull((void*) bufferIn, sizeof(int32_t)*2);
    if(bufferIn[0] == SUCCESS)
    {
        myReadfull((void*) pos, sizeof(float)*4);
        qDebug() << pos[0] << pos[1] << pos[2];
        status = CONTROLLER_IDLE;
        return SUCCESS;
    }
    else
    {
        status = CONTROLLER_IDLE;
        return -1;
    }
}

int Controller::setPosition(float * pos)
{
    char cmdString[1024];
    int32_t dmp[2];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "SET,START,%f,%f,%f,%f\n", pos[0], pos[1], pos[2], pos[3]);
    controller->write(cmdString, strlen(cmdString));
    controller->flush();
    //myReadfull(dmp, sizeof(int32_t)*2);
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "GOTO\n");
    controller->write(cmdString, strlen(cmdString));
    controller->flush();
    //myReadfull(dmp, sizeof(int32_t)*2);
    return 1;
}
