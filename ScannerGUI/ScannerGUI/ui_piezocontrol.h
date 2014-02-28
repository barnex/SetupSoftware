/********************************************************************************
** Form generated from reading UI file 'piezocontrol.ui'
**
** Created: Fri Feb 28 11:03:53 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIEZOCONTROL_H
#define UI_PIEZOCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PiezoControl
{
public:
    QWidget *centralWidget;
    QPushButton *z_down;
    QPushButton *z_up_fast;
    QPushButton *z_up;
    QPushButton *z_down_fast;
    QPushButton *y_right;
    QPushButton *y_right_fast;
    QPushButton *y_left;
    QPushButton *y_left_fast;
    QPushButton *halt;
    QPushButton *x_down_fast;
    QPushButton *x_up_fast;
    QPushButton *x_down;
    QPushButton *x_up;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *x_pos;
    QLineEdit *y_pos;
    QLineEdit *z_pos;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PiezoControl)
    {
        if (PiezoControl->objectName().isEmpty())
            PiezoControl->setObjectName(QString::fromUtf8("PiezoControl"));
        PiezoControl->resize(650, 575);
        centralWidget = new QWidget(PiezoControl);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        z_down = new QPushButton(centralWidget);
        z_down->setObjectName(QString::fromUtf8("z_down"));
        z_down->setGeometry(QRect(180, 310, 61, 61));
        QFont font;
        font.setPointSize(24);
        z_down->setFont(font);
        z_up_fast = new QPushButton(centralWidget);
        z_up_fast->setObjectName(QString::fromUtf8("z_up_fast"));
        z_up_fast->setGeometry(QRect(180, 90, 61, 61));
        z_up_fast->setFont(font);
        z_up = new QPushButton(centralWidget);
        z_up->setObjectName(QString::fromUtf8("z_up"));
        z_up->setGeometry(QRect(180, 160, 61, 61));
        z_up->setFont(font);
        z_down_fast = new QPushButton(centralWidget);
        z_down_fast->setObjectName(QString::fromUtf8("z_down_fast"));
        z_down_fast->setGeometry(QRect(180, 380, 61, 61));
        z_down_fast->setFont(font);
        y_right = new QPushButton(centralWidget);
        y_right->setObjectName(QString::fromUtf8("y_right"));
        y_right->setGeometry(QRect(250, 230, 61, 61));
        y_right->setFont(font);
        y_right_fast = new QPushButton(centralWidget);
        y_right_fast->setObjectName(QString::fromUtf8("y_right_fast"));
        y_right_fast->setGeometry(QRect(320, 230, 61, 61));
        y_right_fast->setFont(font);
        y_left = new QPushButton(centralWidget);
        y_left->setObjectName(QString::fromUtf8("y_left"));
        y_left->setGeometry(QRect(110, 230, 61, 61));
        y_left->setFont(font);
        y_left_fast = new QPushButton(centralWidget);
        y_left_fast->setObjectName(QString::fromUtf8("y_left_fast"));
        y_left_fast->setGeometry(QRect(40, 230, 61, 61));
        y_left_fast->setFont(font);
        halt = new QPushButton(centralWidget);
        halt->setObjectName(QString::fromUtf8("halt"));
        halt->setGeometry(QRect(180, 230, 61, 61));
        halt->setFont(font);
        x_down_fast = new QPushButton(centralWidget);
        x_down_fast->setObjectName(QString::fromUtf8("x_down_fast"));
        x_down_fast->setGeometry(QRect(490, 340, 61, 61));
        x_down_fast->setFont(font);
        x_up_fast = new QPushButton(centralWidget);
        x_up_fast->setObjectName(QString::fromUtf8("x_up_fast"));
        x_up_fast->setGeometry(QRect(490, 130, 61, 61));
        x_up_fast->setFont(font);
        x_down = new QPushButton(centralWidget);
        x_down->setObjectName(QString::fromUtf8("x_down"));
        x_down->setGeometry(QRect(490, 270, 61, 61));
        x_down->setFont(font);
        x_up = new QPushButton(centralWidget);
        x_up->setObjectName(QString::fromUtf8("x_up"));
        x_up->setGeometry(QRect(490, 200, 61, 61));
        x_up->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 50, 241, 41));
        QFont font1;
        font1.setPointSize(19);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(400, 50, 241, 41));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        x_pos = new QLineEdit(centralWidget);
        x_pos->setObjectName(QString::fromUtf8("x_pos"));
        x_pos->setGeometry(QRect(120, 460, 113, 28));
        x_pos->setReadOnly(true);
        y_pos = new QLineEdit(centralWidget);
        y_pos->setObjectName(QString::fromUtf8("y_pos"));
        y_pos->setGeometry(QRect(250, 460, 113, 28));
        y_pos->setReadOnly(true);
        z_pos = new QLineEdit(centralWidget);
        z_pos->setObjectName(QString::fromUtf8("z_pos"));
        z_pos->setGeometry(QRect(380, 460, 113, 28));
        z_pos->setReadOnly(true);
        PiezoControl->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PiezoControl);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 26));
        PiezoControl->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PiezoControl);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PiezoControl->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PiezoControl);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PiezoControl->setStatusBar(statusBar);

        retranslateUi(PiezoControl);
        QObject::connect(z_up_fast, SIGNAL(pressed()), PiezoControl, SLOT(z_up_fast_clicked()));
        QObject::connect(z_up, SIGNAL(pressed()), PiezoControl, SLOT(z_up_clicked()));
        QObject::connect(z_down, SIGNAL(pressed()), PiezoControl, SLOT(z_down_clicked()));
        QObject::connect(z_down_fast, SIGNAL(pressed()), PiezoControl, SLOT(z_down_fast_clicked()));
        QObject::connect(y_left_fast, SIGNAL(pressed()), PiezoControl, SLOT(y_left_fast_clicked()));
        QObject::connect(y_left, SIGNAL(pressed()), PiezoControl, SLOT(y_left_clicked()));
        QObject::connect(y_right, SIGNAL(pressed()), PiezoControl, SLOT(y_right_clicked()));
        QObject::connect(y_right_fast, SIGNAL(pressed()), PiezoControl, SLOT(y_right_fast_clicked()));
        QObject::connect(halt, SIGNAL(pressed()), PiezoControl, SLOT(abort_clicked()));
        QObject::connect(x_up_fast, SIGNAL(pressed()), PiezoControl, SLOT(x_up_fast_clicked()));
        QObject::connect(x_up, SIGNAL(pressed()), PiezoControl, SLOT(x_up_clicked()));
        QObject::connect(x_down, SIGNAL(pressed()), PiezoControl, SLOT(x_down_clicked()));
        QObject::connect(x_down_fast, SIGNAL(pressed()), PiezoControl, SLOT(x_down_fast_clicked()));

        QMetaObject::connectSlotsByName(PiezoControl);
    } // setupUi

    void retranslateUi(QMainWindow *PiezoControl)
    {
        PiezoControl->setWindowTitle(QApplication::translate("PiezoControl", "PiezoControl", 0, QApplication::UnicodeUTF8));
        z_down->setText(QApplication::translate("PiezoControl", "\342\206\223", 0, QApplication::UnicodeUTF8));
        z_up_fast->setText(QApplication::translate("PiezoControl", "\342\207\221", 0, QApplication::UnicodeUTF8));
        z_up->setText(QApplication::translate("PiezoControl", "\342\206\221", 0, QApplication::UnicodeUTF8));
        z_down_fast->setText(QApplication::translate("PiezoControl", "\342\207\223", 0, QApplication::UnicodeUTF8));
        y_right->setText(QApplication::translate("PiezoControl", "\342\206\222", 0, QApplication::UnicodeUTF8));
        y_right_fast->setText(QApplication::translate("PiezoControl", "\342\207\222", 0, QApplication::UnicodeUTF8));
        y_left->setText(QApplication::translate("PiezoControl", "\342\206\220", 0, QApplication::UnicodeUTF8));
        y_left_fast->setText(QApplication::translate("PiezoControl", "\342\207\220", 0, QApplication::UnicodeUTF8));
        halt->setText(QApplication::translate("PiezoControl", "\342\210\205", 0, QApplication::UnicodeUTF8));
        x_down_fast->setText(QApplication::translate("PiezoControl", "\342\207\223", 0, QApplication::UnicodeUTF8));
        x_up_fast->setText(QApplication::translate("PiezoControl", "\342\207\221", 0, QApplication::UnicodeUTF8));
        x_down->setText(QApplication::translate("PiezoControl", "\342\206\223", 0, QApplication::UnicodeUTF8));
        x_up->setText(QApplication::translate("PiezoControl", "\342\206\221", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PiezoControl", "Sample position", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PiezoControl", "Focus", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PiezoControl: public Ui_PiezoControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIEZOCONTROL_H
