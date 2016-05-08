#ifndef POPUP_H
#define POPUP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QApplication>

class Popup: public QWidget
{
    public:
    Popup(QWidget *parent = NULL);
    ~Popup();
    void show_it();
    void set_ui_obj();
};

#endif // POPUP_H
