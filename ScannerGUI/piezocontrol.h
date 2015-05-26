#ifndef PIEZOCONTROL_H
#define PIEZOCONTROL_H

#include <QMainWindow>
#include <QString>
#include <QTextStream>

#include "controller.h"

namespace Ui {
class PiezoControl;
}

class PiezoControl : public QMainWindow {
	Q_OBJECT
public:
	PiezoControl(QWidget *parent = 0);
	~PiezoControl();
	void setPosition(float x, float y, float z);
	void setController(Controller *_c);

public slots:
	void x_up_fast_clicked();
	void x_up_clicked();
	void x_down_clicked();
	void x_down_fast_clicked();

	void y_left_fast_clicked();
	void y_left_clicked();
	void y_right_clicked();
	void y_right_fast_clicked();

	void z_up_fast_clicked();
	void z_up_clicked();
	void z_down_clicked();
	void z_down_fast_clicked();

	void abort_clicked();

protected:
	void changeEvent(QEvent *e);

private:
	Ui::PiezoControl *ui;
	float position[4];
	Controller *c;
};

#endif // PIEZOCONTROL_H
