/********************************************************************************
** Form generated from reading UI file 'piezocontrol.ui'
**
** Created: Thu Feb 27 16:42:53 2014
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
    QPushButton *z_down_fast_2;
    QPushButton *z_up_fast_2;
    QPushButton *z_down_2;
    QPushButton *z_up_2;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PiezoControl)
    {
        if (PiezoControl->objectName().isEmpty())
            PiezoControl->setObjectName(QString::fromUtf8("PiezoControl"));
        PiezoControl->resize(550, 483);
        centralWidget = new QWidget(PiezoControl);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        z_down = new QPushButton(centralWidget);
        z_down->setObjectName(QString::fromUtf8("z_down"));
        z_down->setGeometry(QRect(150, 270, 61, 61));
        QFont font;
        font.setPointSize(24);
        z_down->setFont(font);
        z_up_fast = new QPushButton(centralWidget);
        z_up_fast->setObjectName(QString::fromUtf8("z_up_fast"));
        z_up_fast->setGeometry(QRect(150, 50, 61, 61));
        z_up_fast->setFont(font);
        z_up = new QPushButton(centralWidget);
        z_up->setObjectName(QString::fromUtf8("z_up"));
        z_up->setGeometry(QRect(150, 120, 61, 61));
        z_up->setFont(font);
        z_down_fast = new QPushButton(centralWidget);
        z_down_fast->setObjectName(QString::fromUtf8("z_down_fast"));
        z_down_fast->setGeometry(QRect(150, 340, 61, 61));
        z_down_fast->setFont(font);
        y_right = new QPushButton(centralWidget);
        y_right->setObjectName(QString::fromUtf8("y_right"));
        y_right->setGeometry(QRect(220, 190, 61, 61));
        y_right->setFont(font);
        y_right_fast = new QPushButton(centralWidget);
        y_right_fast->setObjectName(QString::fromUtf8("y_right_fast"));
        y_right_fast->setGeometry(QRect(290, 190, 61, 61));
        y_right_fast->setFont(font);
        y_left = new QPushButton(centralWidget);
        y_left->setObjectName(QString::fromUtf8("y_left"));
        y_left->setGeometry(QRect(80, 190, 61, 61));
        y_left->setFont(font);
        y_left_fast = new QPushButton(centralWidget);
        y_left_fast->setObjectName(QString::fromUtf8("y_left_fast"));
        y_left_fast->setGeometry(QRect(10, 190, 61, 61));
        y_left_fast->setFont(font);
        halt = new QPushButton(centralWidget);
        halt->setObjectName(QString::fromUtf8("halt"));
        halt->setGeometry(QRect(150, 190, 61, 61));
        halt->setFont(font);
        z_down_fast_2 = new QPushButton(centralWidget);
        z_down_fast_2->setObjectName(QString::fromUtf8("z_down_fast_2"));
        z_down_fast_2->setGeometry(QRect(460, 300, 61, 61));
        z_down_fast_2->setFont(font);
        z_up_fast_2 = new QPushButton(centralWidget);
        z_up_fast_2->setObjectName(QString::fromUtf8("z_up_fast_2"));
        z_up_fast_2->setGeometry(QRect(460, 90, 61, 61));
        z_up_fast_2->setFont(font);
        z_down_2 = new QPushButton(centralWidget);
        z_down_2->setObjectName(QString::fromUtf8("z_down_2"));
        z_down_2->setGeometry(QRect(460, 230, 61, 61));
        z_down_2->setFont(font);
        z_up_2 = new QPushButton(centralWidget);
        z_up_2->setObjectName(QString::fromUtf8("z_up_2"));
        z_up_2->setGeometry(QRect(460, 160, 61, 61));
        z_up_2->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 10, 241, 41));
        QFont font1;
        font1.setPointSize(19);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(370, 10, 241, 41));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        PiezoControl->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PiezoControl);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 550, 26));
        PiezoControl->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PiezoControl);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PiezoControl->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PiezoControl);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PiezoControl->setStatusBar(statusBar);

        retranslateUi(PiezoControl);

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
        z_down_fast_2->setText(QApplication::translate("PiezoControl", "\342\207\223", 0, QApplication::UnicodeUTF8));
        z_up_fast_2->setText(QApplication::translate("PiezoControl", "\342\207\221", 0, QApplication::UnicodeUTF8));
        z_down_2->setText(QApplication::translate("PiezoControl", "\342\206\223", 0, QApplication::UnicodeUTF8));
        z_up_2->setText(QApplication::translate("PiezoControl", "\342\206\221", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PiezoControl", "Sample position", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PiezoControl", "Focus", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PiezoControl: public Ui_PiezoControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIEZOCONTROL_H
