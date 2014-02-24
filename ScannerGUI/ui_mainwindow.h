/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Feb 24 09:37:18 2014
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
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
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
    QLineEdit *channel0_out_0;
    QLineEdit *channel0_out_2;
    QLineEdit *channel0_out_3;
    QLineEdit *channel0_out_4;
    QLineEdit *channel0_out_5;
    QLineEdit *channel0_out_6;
    QLineEdit *channel0_out_7;
    QLineEdit *channel0_out_1;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(427, 344);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        channel0_out_0 = new QLineEdit(centralWidget);
        channel0_out_0->setObjectName(QString::fromUtf8("channel0_out_0"));
        channel0_out_0->setGeometry(QRect(160, 20, 113, 28));
        channel0_out_0->setReadOnly(true);
        channel0_out_2 = new QLineEdit(centralWidget);
        channel0_out_2->setObjectName(QString::fromUtf8("channel0_out_2"));
        channel0_out_2->setGeometry(QRect(160, 80, 113, 28));
        channel0_out_2->setReadOnly(true);
        channel0_out_3 = new QLineEdit(centralWidget);
        channel0_out_3->setObjectName(QString::fromUtf8("channel0_out_3"));
        channel0_out_3->setGeometry(QRect(160, 110, 113, 28));
        channel0_out_3->setReadOnly(true);
        channel0_out_4 = new QLineEdit(centralWidget);
        channel0_out_4->setObjectName(QString::fromUtf8("channel0_out_4"));
        channel0_out_4->setGeometry(QRect(160, 140, 113, 28));
        channel0_out_4->setReadOnly(true);
        channel0_out_5 = new QLineEdit(centralWidget);
        channel0_out_5->setObjectName(QString::fromUtf8("channel0_out_5"));
        channel0_out_5->setGeometry(QRect(160, 170, 113, 28));
        channel0_out_5->setReadOnly(true);
        channel0_out_6 = new QLineEdit(centralWidget);
        channel0_out_6->setObjectName(QString::fromUtf8("channel0_out_6"));
        channel0_out_6->setGeometry(QRect(160, 200, 113, 28));
        channel0_out_6->setReadOnly(true);
        channel0_out_7 = new QLineEdit(centralWidget);
        channel0_out_7->setObjectName(QString::fromUtf8("channel0_out_7"));
        channel0_out_7->setGeometry(QRect(160, 230, 113, 28));
        channel0_out_7->setReadOnly(true);
        channel0_out_1 = new QLineEdit(centralWidget);
        channel0_out_1->setObjectName(QString::fromUtf8("channel0_out_1"));
        channel0_out_1->setGeometry(QRect(160, 50, 113, 28));
        channel0_out_1->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 30, 81, 18));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 240, 81, 18));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 427, 26));
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
        label->setText(QApplication::translate("MainWindow", "Channel 0:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Channel 7:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
