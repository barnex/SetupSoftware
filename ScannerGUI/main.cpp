#include <QtGui/QApplication>
#include "mainwindow.h"
#include "updateThread.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    updateThread myThread;
    Controller *controller = new Controller();
    controller->init(5000);

    MainWindow w;

    myThread.setController( controller );
    QObject::connect(&myThread, SIGNAL(sendValues(float *)), &w, SLOT(setValues(float *)), Qt::QueuedConnection);



    float start[4], current[4], xscan[4], yscan[4];
    int pixels, t_settle;
    controller->getCurrentPosition(current);
    controller->getStartPosition(start);
    controller->getIInc(xscan);
    controller->getJInc(yscan);
    controller->getPixels(&pixels);
    controller->getTSettle(&t_settle);
    w.updateParamsp(start, current, xscan, yscan, pixels, t_settle);
    myThread.start();

    w.show();
    a.exec();
    myThread.wait();
    free( controller );
    return 0;
}
