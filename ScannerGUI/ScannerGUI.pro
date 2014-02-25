# -------------------------------------------------
# Project created by QtCreator 2014-02-21T16:15:30
# -------------------------------------------------
TARGET = ScannerGUI
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    updateThread.cpp \
    controller.cpp \
    scanthread.cpp
HEADERS += mainwindow.h \
    updateThread.h \
    controller.h \
    scanthread.h
FORMS += mainwindow.ui
QT += network
LIBS += -libqwt
