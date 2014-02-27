#include "piezocontrol.h"
#include "ui_piezocontrol.h"

PiezoControl::PiezoControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PiezoControl)
{
    ui->setupUi(this);
}

PiezoControl::~PiezoControl()
{
    delete ui;
}

void PiezoControl::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
