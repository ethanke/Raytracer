#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T23:37:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Raytracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addobjectpopup.cpp \
    scene.cpp

HEADERS  += mainwindow.h \
    addobjectpopup.h \
    scene.h

FORMS    += mainwindow.ui
