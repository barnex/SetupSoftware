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

void MainWindow::setValues(float *values)
{
    QString entry;
    QTextStream(&entry) << values[0] << " V";
    ui->channel0_out_0->setText(entry);

    entry = "";
    QTextStream(&entry) << values[1] << " V";
    ui->channel0_out_1->setText(entry);

        entry = "";
    QTextStream(&entry) << values[2] << " V";
    ui->channel0_out_2->setText(entry);

        entry = "";
    QTextStream(&entry) << values[3] << " V";
    ui->channel0_out_3->setText(entry);

        entry = "";
    QTextStream(&entry) << values[4] << " V";
    ui->channel0_out_4->setText(entry);

        entry = "";
    QTextStream(&entry) << values[5] << " V";
    ui->channel0_out_5->setText(entry);

        entry = "";
    QTextStream(&entry) << values[6] << " V";
    ui->channel0_out_6->setText(entry);

        entry = "";
    QTextStream(&entry) << values[7] << " V";
    ui->channel0_out_7->setText(entry);
}
