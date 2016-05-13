#ifndef POPUP_H
#define POPUP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <object.h>
#include <qwidget.h>
#include "sphere.h"
#include "mainwindow.h"

class MyPopup: public QWidget
{
    Q_OBJECT

public:
    MyPopup(MainWindow *mw);
    ~MyPopup();
    void show_it();
    void set_ui_obj(Object *object);
    void keyPressEvent(QKeyEvent *e);
    QWidget *parent;

private:
    QPushButton *Apply;
    QLabel *CenterX;
    QLabel *CenterY;
    QLabel *CenterZ;
    QLineEdit *EditX;
    QLineEdit *EditY;
    QLineEdit *EditZ;
    Object *object;
    MainWindow *mw;
private slots:
     void setValueObj();

};

#else
    class MyPopup;

#endif // POPUP_H
