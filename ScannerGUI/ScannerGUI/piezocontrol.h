#ifndef PIEZOCONTROL_H
#define PIEZOCONTROL_H

#include <QMainWindow>

namespace Ui {
    class PiezoControl;
}

class PiezoControl : public QMainWindow {
    Q_OBJECT
public:
    PiezoControl(QWidget *parent = 0);
    ~PiezoControl();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PiezoControl *ui;
};

#endif // PIEZOCONTROL_H
