#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Controller *ctrlr) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = ctrlr;
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

void MainWindow::setButtonClicked()
{
    float buffer[4];

    // First read the current position and send to the controller
    memset(buffer, 0, sizeof(float)*4);
    buffer[0] = ui->current_x->text().toFloat();
    buffer[1] = ui->current_y->text().toFloat();
    buffer[2] = ui->current_z->text().toFloat();
    buffer[3] = ui->current_aux->text().toFloat();
    controller->setCurrentPosition(buffer);

    // Start position
    memset(buffer, 0, sizeof(float)*4);
    buffer[0] = ui->start_x->text().toFloat();
    buffer[1] = ui->start_y->text().toFloat();
    buffer[2] = ui->start_z->text().toFloat();
    buffer[3] = ui->start_aux->text().toFloat();
    controller->setStartPosition(buffer);

    // Scan-x vector
    memset(buffer, 0, sizeof(float)*4);
    buffer[0] = ui->scanx_x->text().toFloat();
    buffer[1] = ui->scanx_y->text().toFloat();
    buffer[2] = ui->scanx_z->text().toFloat();
    buffer[3] = ui->scanx_aux->text().toFloat();
    controller->setIInc(buffer);

    // Scan-y vector
    memset(buffer, 0, sizeof(float)*4);
    buffer[0] = ui->scany_x->text().toFloat();
    buffer[1] = ui->scany_y->text().toFloat();
    buffer[2] = ui->scany_z->text().toFloat();
    buffer[3] = ui->scany_aux->text().toFloat();
    controller->setJInc(buffer);

    // Pixels
    int iBuffer = 0;
    iBuffer = ui->pixels->text().toInt();
    controller->setPixels(&iBuffer);

    // Settle time
    iBuffer = 0;
    iBuffer = ui->tsettle->text().toInt();
    if(iBuffer < 2)
    {
        iBuffer = 2;
    }
    controller->setTSettle(&iBuffer);
}

void MainWindow::resetButtonClicked()
{
    qDebug() << "Clicked a button!";
}

void MainWindow::abortButtonClicked()
{
    qDebug() << "Clicked a button!";
}

void MainWindow::scanButtonClicked()
{
    qDebug() << "Clicked a button!";
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

/*
void MainWindow::updateParams(float *start, float *current, float *xscan, float *yscan, int pixels, int t_settle)
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
void MainWindow::updateParamsp(float *start, float *current, float *xscan, float *yscan, int pixels, int t_settle)
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
*/
