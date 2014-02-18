#include <QtGui/QApplication>
#include "updateThread.h"
#include "mainwindow.h"
#include <QMutex>#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>


int initSocket(char *server_name, int portno);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMutex mutex;
    int sockfd = 0;
    MainWindow w;
    updateThread thread;

    sockfd = initSocket("dynalab.ugent.be", 2000);

    thread.mutex = &mutex;
    thread.sockfd = &sockfd;

    QObject::connect(&thread, SIGNAL(sendValues(double *)), &w, SLOT(setValues(double *)), Qt::QueuedConnection);

    w.show();
    thread.start();
    a.exec();
    thread.wait();
    return 0;
}

int initSocket(char *server_name, int portno)
{
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error: Could not create socket\n");
        return -1;
    }

    server = gethostbyname(server_name);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = portno;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("Error: Could not connect\n");
        return -1;
    }

    return sockfd;
}
