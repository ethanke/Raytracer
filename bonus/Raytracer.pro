#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T23:37:46
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Raytracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addobjectpopup.cpp \
    scene.cpp \
    xmldom.cpp

HEADERS  += mainwindow.h \
    addobjectpopup.h \
    scene.h \
    xmldom.h

FORMS    += mainwindow.ui
