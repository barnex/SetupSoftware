#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QDebug>
#include "controller.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0, Controller *ctrlr = NULL);
    ~MainWindow();
    void updateStart( float *start);
    void updateCurrent( float *current );
    void updateXScan( float *xscan );
    void updateYScan( float *yscan );
    void updatePixels( int *pixels );
    void updateTSettle( int *tsettle );

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    Controller *controller;

private slots:
    void setValues( float *values );
    void setButtonClicked();
    void resetButtonClicked();
    void abortButtonClicked();
    void scanButtonClicked();

};

#endif // MAINWINDOW_H
