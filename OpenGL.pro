QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp  \
        qgl_tutorial06.cpp

HEADERS += \
        mainwindow.h    \
        qgl_tutorial06.h

FORMS += \
        mainwindow.ui

RESOURCES += GLShaders.qrc