/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Feb 24 14:20:01 2014
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
#include <QtGui/QPushButton>
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
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *start_x;
    QLineEdit *start_y;
    QLineEdit *start_z;
    QLineEdit *start_aux;
    QLineEdit *current_aux;
    QLineEdit *current_y;
    QLineEdit *current_z;
    QLineEdit *current_x;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *scanx_aux;
    QLineEdit *scanx_y;
    QLineEdit *scanx_z;
    QLineEdit *scanx_x;
    QLineEdit *scany_aux;
    QLineEdit *scany_y;
    QLineEdit *scany_z;
    QLineEdit *scany_x;
    QLineEdit *pixels;
    QLineEdit *tsettle;
    QLabel *label_13;
    QPushButton *setButton;
    QPushButton *scanButton;
    QPushButton *abortButton;
    QPushButton *resetButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(891, 494);
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
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(360, 60, 68, 18));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(360, 100, 68, 18));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(320, 140, 111, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(320, 180, 111, 20));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(360, 230, 71, 18));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(280, 270, 151, 20));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        start_x = new QLineEdit(centralWidget);
        start_x->setObjectName(QString::fromUtf8("start_x"));
        start_x->setGeometry(QRect(440, 60, 71, 28));
        start_x->setReadOnly(true);
        start_y = new QLineEdit(centralWidget);
        start_y->setObjectName(QString::fromUtf8("start_y"));
        start_y->setGeometry(QRect(520, 60, 71, 28));
        start_y->setReadOnly(true);
        start_z = new QLineEdit(centralWidget);
        start_z->setObjectName(QString::fromUtf8("start_z"));
        start_z->setGeometry(QRect(600, 60, 71, 28));
        start_z->setReadOnly(true);
        start_aux = new QLineEdit(centralWidget);
        start_aux->setObjectName(QString::fromUtf8("start_aux"));
        start_aux->setGeometry(QRect(680, 60, 71, 28));
        start_aux->setReadOnly(true);
        current_aux = new QLineEdit(centralWidget);
        current_aux->setObjectName(QString::fromUtf8("current_aux"));
        current_aux->setGeometry(QRect(680, 100, 71, 28));
        current_aux->setReadOnly(true);
        current_y = new QLineEdit(centralWidget);
        current_y->setObjectName(QString::fromUtf8("current_y"));
        current_y->setGeometry(QRect(520, 100, 71, 28));
        current_y->setReadOnly(true);
        current_z = new QLineEdit(centralWidget);
        current_z->setObjectName(QString::fromUtf8("current_z"));
        current_z->setGeometry(QRect(600, 100, 71, 28));
        current_z->setReadOnly(true);
        current_x = new QLineEdit(centralWidget);
        current_x->setObjectName(QString::fromUtf8("current_x"));
        current_x->setGeometry(QRect(440, 100, 71, 28));
        current_x->setReadOnly(true);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(440, 40, 68, 18));
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(520, 40, 68, 18));
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(600, 40, 68, 18));
        label_11->setAlignment(Qt::AlignCenter);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(680, 40, 68, 18));
        label_12->setAlignment(Qt::AlignCenter);
        scanx_aux = new QLineEdit(centralWidget);
        scanx_aux->setObjectName(QString::fromUtf8("scanx_aux"));
        scanx_aux->setGeometry(QRect(680, 140, 71, 28));
        scanx_aux->setReadOnly(true);
        scanx_y = new QLineEdit(centralWidget);
        scanx_y->setObjectName(QString::fromUtf8("scanx_y"));
        scanx_y->setGeometry(QRect(520, 140, 71, 28));
        scanx_y->setReadOnly(true);
        scanx_z = new QLineEdit(centralWidget);
        scanx_z->setObjectName(QString::fromUtf8("scanx_z"));
        scanx_z->setGeometry(QRect(600, 140, 71, 28));
        scanx_z->setReadOnly(true);
        scanx_x = new QLineEdit(centralWidget);
        scanx_x->setObjectName(QString::fromUtf8("scanx_x"));
        scanx_x->setGeometry(QRect(440, 140, 71, 28));
        scanx_x->setReadOnly(true);
        scany_aux = new QLineEdit(centralWidget);
        scany_aux->setObjectName(QString::fromUtf8("scany_aux"));
        scany_aux->setGeometry(QRect(680, 180, 71, 28));
        scany_aux->setReadOnly(true);
        scany_y = new QLineEdit(centralWidget);
        scany_y->setObjectName(QString::fromUtf8("scany_y"));
        scany_y->setGeometry(QRect(520, 180, 71, 28));
        scany_y->setReadOnly(true);
        scany_z = new QLineEdit(centralWidget);
        scany_z->setObjectName(QString::fromUtf8("scany_z"));
        scany_z->setGeometry(QRect(600, 180, 71, 28));
        scany_z->setReadOnly(true);
        scany_x = new QLineEdit(centralWidget);
        scany_x->setObjectName(QString::fromUtf8("scany_x"));
        scany_x->setGeometry(QRect(440, 180, 71, 28));
        scany_x->setReadOnly(true);
        pixels = new QLineEdit(centralWidget);
        pixels->setObjectName(QString::fromUtf8("pixels"));
        pixels->setGeometry(QRect(440, 220, 101, 28));
        pixels->setReadOnly(true);
        tsettle = new QLineEdit(centralWidget);
        tsettle->setObjectName(QString::fromUtf8("tsettle"));
        tsettle->setGeometry(QRect(440, 260, 101, 28));
        tsettle->setReadOnly(true);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(550, 270, 31, 20));
        label_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        setButton = new QPushButton(centralWidget);
        setButton->setObjectName(QString::fromUtf8("setButton"));
        setButton->setGeometry(QRect(160, 320, 90, 29));
        scanButton = new QPushButton(centralWidget);
        scanButton->setObjectName(QString::fromUtf8("scanButton"));
        scanButton->setGeometry(QRect(270, 320, 90, 29));
        abortButton = new QPushButton(centralWidget);
        abortButton->setObjectName(QString::fromUtf8("abortButton"));
        abortButton->setGeometry(QRect(380, 320, 90, 29));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        abortButton->setPalette(palette);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        abortButton->setFont(font);
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(490, 320, 90, 29));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 891, 26));
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
        label_3->setText(QApplication::translate("MainWindow", "Start:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Current:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "X Scan Vector:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Y Scan Vector:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Pixels:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Settle time per pixel:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "x-axis", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "y-axis", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "z-axis", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "auxiliary", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "ms", 0, QApplication::UnicodeUTF8));
        setButton->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        scanButton->setText(QApplication::translate("MainWindow", "Scan", 0, QApplication::UnicodeUTF8));
        abortButton->setText(QApplication::translate("MainWindow", "Abort", 0, QApplication::UnicodeUTF8));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
