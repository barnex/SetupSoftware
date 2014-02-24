#include <QtGui/QApplication>
#include "mainwindow.h"
#include "updateThread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    updateThread myThread;

    MainWindow w;

    myThread.initSocket(5000);
    QObject::connect(&myThread, SIGNAL(sendValues(float *)), &w, SLOT(setValues(float *)), Qt::QueuedConnection);
    myThread.start();
    w.show();
    a.exec();
    myThread.wait();
    return 0;
}
