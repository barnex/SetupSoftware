# -------------------------------------------------
# Project created by QtCreator 2014-02-27T16:25:50
# -------------------------------------------------
QT += network
TARGET = ScannerGUI
TEMPLATE = app
SOURCES += main.cpp \
    piezocontrol.cpp \
    controller.cpp \
    socket.c \
    io.c
HEADERS += piezocontrol.h \
    controller.h \
    socket.h \
    io.h \
    errors.h
FORMS += piezocontrol.ui
