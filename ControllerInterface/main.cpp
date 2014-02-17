#include <QtGui/QApplication>
#include "updateThread.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    updateThread thread;
    QObject::connect(&thread, SIGNAL(sendValues(double *)), &w, SLOT(setValues(double *)), Qt::QueuedConnection);
    thread.start();
    thread.start();
    a.exec();
    thread.wait();
    return 0;
}
