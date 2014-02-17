/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Feb 17 16:34:02 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    QLCDNumber *lcdNumber_4;
    QLCDNumber *lcdNumber_5;
    QLCDNumber *lcdNumber_6;
    QLCDNumber *lcdNumber_7;
    QLCDNumber *lcdNumber_8;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(558, 407);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(30, 50, 171, 51));
        lcdNumber_2 = new QLCDNumber(centralWidget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(30, 110, 171, 51));
        lcdNumber_3 = new QLCDNumber(centralWidget);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(30, 190, 171, 51));
        lcdNumber_4 = new QLCDNumber(centralWidget);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));
        lcdNumber_4->setGeometry(QRect(30, 250, 171, 51));
        lcdNumber_5 = new QLCDNumber(centralWidget);
        lcdNumber_5->setObjectName(QString::fromUtf8("lcdNumber_5"));
        lcdNumber_5->setGeometry(QRect(310, 50, 171, 51));
        lcdNumber_6 = new QLCDNumber(centralWidget);
        lcdNumber_6->setObjectName(QString::fromUtf8("lcdNumber_6"));
        lcdNumber_6->setGeometry(QRect(310, 190, 171, 51));
        lcdNumber_7 = new QLCDNumber(centralWidget);
        lcdNumber_7->setObjectName(QString::fromUtf8("lcdNumber_7"));
        lcdNumber_7->setGeometry(QRect(310, 110, 171, 51));
        lcdNumber_8 = new QLCDNumber(centralWidget);
        lcdNumber_8->setObjectName(QString::fromUtf8("lcdNumber_8"));
        lcdNumber_8->setGeometry(QRect(310, 250, 171, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 50, 31, 51));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 110, 31, 51));
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 190, 31, 51));
        label_3->setFont(font);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(210, 250, 31, 51));
        label_4->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(490, 50, 68, 51));
        label_5->setFont(font);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(490, 110, 68, 51));
        label_6->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(490, 190, 68, 51));
        label_7->setFont(font);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(490, 250, 68, 51));
        label_8->setFont(font);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 10, 221, 31));
        QFont font1;
        font1.setPointSize(16);
        label_9->setFont(font1);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 50, 31, 41));
        QFont font2;
        font2.setPointSize(19);
        label_10->setFont(font2);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 110, 31, 41));
        label_11->setFont(font);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 190, 31, 41));
        label_12->setFont(font);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 260, 31, 41));
        label_13->setFont(font);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(290, 50, 31, 41));
        label_14->setFont(font);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(290, 110, 31, 41));
        label_15->setFont(font);
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(290, 190, 31, 41));
        label_16->setFont(font);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(290, 260, 31, 41));
        label_17->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 558, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Input channels", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
