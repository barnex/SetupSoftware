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

void PiezoControl::setController(Controller *_c)
{
    c = _c;
}

void PiezoControl::setPosition(float x, float y, float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = 0.0;

    QString pos_string;
    QTextStream(&pos_string) << x;
    ui->x_pos->setText(pos_string);

    pos_string = "";
    QTextStream(&pos_string) << y;
    ui->y_pos->setText(pos_string);

    pos_string = "";
    QTextStream(&pos_string) << z;
    ui->z_pos->setText(pos_string);
}

void PiezoControl::x_up_fast_clicked()
{
    if(position[0] < 0.95)
    {
        position[0] += 0.05;
    }
    else
    {
        position[0] = 1.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::x_up_clicked()
{
    if(position[0] < 0.99)
    {
        position[0] += 0.01;
    }
    else
    {
        position[0] = 1.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::x_down_clicked()
{
    if(position[0] > 0.01)
    {
        position[0] -= 0.01;
    }
    else
    {
        position[0] = 0.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::x_down_fast_clicked()
{
    if(position[0] > 0.05)
    {
        position[0] -= 0.05;
    }
    else
    {
        position[0] = 0.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::y_left_fast_clicked()
{
    if(position[1] > 0.05)
    {
        position[1] -= 0.05;
    }
    else
    {
        position[1] = 0.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::y_left_clicked()
{
    if(position[1] > 0.01)
    {
        position[1] -= 0.01;
    }
    else
    {
        position[1] = 0.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::y_right_clicked()
{
    if(position[1] < 0.99)
    {
        position[1] += 0.01;
    }
    else
    {
        position[1] = 1.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::y_right_fast_clicked()
{
    if(position[1] < 0.95)
    {
        position[1] += 0.05;
    }
    else
    {
        position[1] = 1.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::z_up_fast_clicked()
{
    if(position[2] < 0.95)
    {
        position[2] += 0.05;
    }
    else
    {
        position[2] = 1.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::z_up_clicked()
{
    if(position[2] < 0.99)
    {
        position[2] += 0.01;
    }
    else
    {
        position[2] = 1.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::z_down_clicked()
{
    if(position[2] > 0.01)
    {
        position[2] -= 0.01;
    }
    else
    {
        position[2] = 0.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::z_down_fast_clicked()
{
    if(position[2] > 0.05)
    {
        position[2] -= 0.05;
    }
    else
    {
        position[2] = 0.0;
    }
    c->setPosition(position);
    setPosition(position[0], position[1], position[2]);
}

void PiezoControl::abort_clicked()
{
    c->abort();
}

