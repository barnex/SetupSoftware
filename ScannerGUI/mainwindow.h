#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateParamsp(float *start, float *current, float *xscan, float *yscan, int pixels, int t_settle);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
private slots:
    void setValues( float *values );
    void updateParams(float *start, float *current, float *xscan, float *yscan, int pixels, int t_settle);
};

#endif // MAINWINDOW_H
