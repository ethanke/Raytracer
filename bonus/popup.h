#ifndef POPUP_H
#define POPUP_H

#include <QMainWindow>
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
    void show_it();
    void set_ui_obj(Object *object);
    void keyPressEvent(QKeyEvent *e);

};

#endif // POPUP_H
