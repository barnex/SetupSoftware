#include "controller.h"

Controller::Controller(void)
{
    controller = new QTcpSocket();

    status = CONTROLLER_IDLE;
}

Controller::~Controller()
{
    controller->close();
}

int Controller::init(int portno)
{
    controller->connectToHost("localhost", portno, QIODevice::ReadWrite);
    // Request the current position of the piezo and set as current position
    memset(currentPosition, 0, sizeof(float)*4);
    getCurrentPosition( currentPosition );
    // Set this as the start position
    memmove( startPosition, currentPosition, sizeof(float)*4);
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "SET,START,%f,%f,%f,%f\n", startPosition[0], startPosition[1], startPosition[2], startPosition[3]);
    controller->write(cmdString, strlen(cmdString));

    // set all other values to zero and let the controller know
    memset(IInc, 0, sizeof(float)*4);
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,IINC,0.0,0.0,0.0,0.0\n");
    controller->write(cmdString, strlen(cmdString));

    memset(JInc, 0, sizeof(float)*4);
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,JINC,0.0,0.0,0.0,0.0\n");
    controller->write(cmdString, strlen(cmdString));

    pixels = 0;
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,PIXELS,0.0\n");
    controller->write(cmdString, strlen(cmdString));

    t_settle = 2;
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,TSETTLE,2.0\n");
    controller->write(cmdString, strlen(cmdString));

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

int Controller::getStatus()
{
    return status;
}

int Controller::singleMeasurement(float *results)
{
    int32_t bufferIn[2] = {0, 0};
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "MEAS\n");

    controller->write(cmdString, strlen(cmdString));
    myReadfull((void*) bufferIn, sizeof(int32_t)*2);

    if( bufferIn[0] == SUCCESS)
    {
        myReadfull((void *)results, sizeof(float)*8);
        return SUCCESS;
    }
    else
    {
        return -1;
    }
}

int Controller::getCurrentPosition( float *pos )
{
    int32_t bufferIn[2] = {0, 0};
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "GET,POSITION\n");

    controller->write(cmdString, strlen(cmdString));
    myReadfull((void*) bufferIn, sizeof(int32_t)*2);
    if(bufferIn[0] == SUCCESS)
    {
        myReadfull((void*) pos, sizeof(float)*4);
        return SUCCESS;
    }
    else
    {
        return -1;
    }
}
