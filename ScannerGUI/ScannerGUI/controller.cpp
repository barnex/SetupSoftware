#include "controller.h"

Controller::Controller(void)
{
    sockfd = 0;
}

Controller::~Controller()
{
    close(sockfd);
}

int Controller::init(int portno)
{
    initClient( &sockfd, portno );
    t_settle = 10;
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString,"SET,TSETTLE,10.0\n");
    write(sockfd, cmdString, strlen(cmdString));
    int32_t dmp[2] = {0, 0};
    myReadfull(sockfd, dmp, sizeof(int32_t)*2);
    qDebug() << dmp[0] << " and " << dmp[1];
    usleep(100);

    return SUCCESS;
}

int Controller::abort()
{
    char cmdString[] = "ABORT\n";
    write(sockfd, cmdString, strlen(cmdString));
    //controller->flush();
    int32_t dmp[2] = {0, 0};
    myReadfull(sockfd, dmp, sizeof(int32_t)*2);
    return 1;
}

int Controller::getPosition( float *pos )
{
    int32_t bufferIn[2] = {0, 0};
    char cmdString[1024];
    memset(cmdString, 0, 1024);
    sprintf(cmdString, "GET,POSITION\n");

    write(sockfd, cmdString, strlen(cmdString));\
    //controller->flush();
    myReadfull(sockfd, bufferIn, sizeof(int32_t)*2);
    if(bufferIn[0] == SUCCESS)
    {
        myReadfull(sockfd, (void*) pos, sizeof(float)*4);
        qDebug() << pos[0] << pos[1] << pos[2];
        return SUCCESS;
    }
    else
    {
        return -1;
    }
}

int Controller::setPosition(float * pos)
{
    char cmdString[1024];
    int32_t dmp[2];

    memset(cmdString, 0, 1024);
    sprintf(cmdString, "SET,START,%f,%f,%f,%f\n", pos[0], pos[1], pos[2], pos[3]);
    write(sockfd, cmdString, strlen(cmdString));
    myReadfull(sockfd, dmp, sizeof(int32_t)*2);

    memset(cmdString, 0, 1024);
    sprintf(cmdString, "GOTO\n");
    write(sockfd, cmdString, strlen(cmdString));
    myReadfull(sockfd, dmp, sizeof(int32_t)*2);

    return 1;
}
