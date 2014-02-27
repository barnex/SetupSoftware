#include <QtGui/QApplication>
#include "piezocontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PiezoControl w;
    w.show();
    return a.exec();
}
