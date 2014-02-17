#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
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

void MainWindow::setValues(double *values)
{
    qDebug() << "Updating values";
    ui->lcdNumber->display(values[0]);
    ui->lcdNumber_2->display(values[1]);
    ui->lcdNumber_3->display(values[2]);
    ui->lcdNumber_4->display(values[3]);
    ui->lcdNumber_5->display(values[4]);
    ui->lcdNumber_6->display(values[5]);
    ui->lcdNumber_7->display(values[6]);
    ui->lcdNumber_8->display(values[7]);
}
