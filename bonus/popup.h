#ifndef POPUP_H
#define POPUP_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QApplication>
#include <object.h>

class MyPopup: public QWidget
{
    Q_OBJECT

public:
    MyPopup();
    ~MyPopup();

private:
    void show_it();
    void set_ui_obj(Object *object);

};

#endif // POPUP_H
