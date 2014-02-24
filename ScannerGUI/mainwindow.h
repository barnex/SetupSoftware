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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
private slots:
    void setValues( float *values );
    void updateParams(float *start, float *current, float *xscan, float *yscan, float pixels, float t_settle);
};

#endif // MAINWINDOW_H
