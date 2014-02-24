#include <QtGui/QApplication>
#include "mainwindow.h"
#include "updateThread.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    updateThread myThread;
    Controller *controller = new Controller();

    MainWindow w;

    myThread.setController( controller );
    QObject::connect(&myThread, SIGNAL(sendValues(float *)), &w, SLOT(setValues(float *)), Qt::QueuedConnection);
    QObject::connect(&myThread, SIGNAL(paramsChanged(float *)), &w, SLOT(updateParams(float *)), Qt::QueuedConnection);
    controller->init(5000);

    myThread.start();

    w.show();
    a.exec();
    myThread.wait();
    free( controller );
    return 0;
}
