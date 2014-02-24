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

void MainWindow::updateParams(float *start, float *current, float *xscan, float *yscan, float pixels, float t_settle)
{
    QString entry = "";
    QTextStream(&entry) << start[0];
    ui->start_x->setText(entry);

    entry = "";
    QTextStream(&entry) << start[1];
    ui->start_y->setText(entry);

    entry = "";
    QTextStream(&entry) << start[2];
    ui->start_z->setText(entry);

    entry = "";
    QTextStream(&entry) << start[3];
    ui->start_aux->setText(entry);

    entry = "";
    QTextStream(&entry) << current[0];
    ui->current_x->setText(entry);

    entry = "";
    QTextStream(&entry) << current[1];
    ui->current_y->setText(entry);

    entry = "";
    QTextStream(&entry) << current[2];
    ui->current_z->setText(entry);

    entry = "";
    QTextStream(&entry) << current[3];
    ui->current_aux->setText(entry);

    entry = "";
    QTextStream(&entry) << xscan[0];
    ui->scanx_x->setText(entry);

    entry = "";
    QTextStream(&entry) << xscan[1];
    ui->scanx_y->setText(entry);

    entry = "";
    QTextStream(&entry) << xscan[2];
    ui->scanx_z->setText(entry);

    entry = "";
    QTextStream(&entry) << xscan[3];
    ui->scanx_aux->setText(entry);


    entry = "";
    QTextStream(&entry) << yscan[0];
    ui->scany_x->setText(entry);

    entry = "";
    QTextStream(&entry) << yscan[1];
    ui->scany_y->setText(entry);

    entry = "";
    QTextStream(&entry) << yscan[2];
    ui->scany_z->setText(entry);

    entry = "";
    QTextStream(&entry) << yscan[3];
    ui->scany_aux->setText(entry);

    entry = "";
    QTextStream(&entry) << pixels;
    ui->pixels->setText(entry);

    entry = "";
    QTextStream(&entry) << t_settle;
    ui->tsettle->setText(entry);
}
