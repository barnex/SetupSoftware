#include <QApplication>
#include "piezocontrol.h"
#include "controller.h"
#include <QMutex>
#include <QTcpSocket>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PiezoControl w;
    Controller c;

    w.setController(&c);
    float position[4] = {0.0, 0.0, 0.0, 0.0};
    c.init(5000);
    c.getPosition(position);
    w.setPosition(position[0], position[1], position[2]);
    w.show();
    return a.exec();
}
