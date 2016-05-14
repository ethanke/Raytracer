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
#include <QComboBox>
#include <object.h>
#include <qwidget.h>
#include "sphere.h"
#include "mainwindow.h"
#include "vector2f.h"

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
    int typeSelected = 0;
    /*
     * 0 : sphere
     */
    void set_ui_selectobj();
    void set_ui_addobj();
    void set_layout_sphere(QGridLayout *mainLayout);
private:
    QPushButton *Apply;
    QLabel *CenterX;
    QLabel *CenterY;
    QLabel *CenterZ;
    QLabel *matLab;
    QLabel *radLab;
    QLineEdit *EditRad;
    QLineEdit *EditX;
    QLineEdit *EditY;
    QLineEdit *EditZ;
    QComboBox *matList;
    Object *object;
    MainWindow *mw;
    QComboBox *SelectMat;
    QPushButton *createSph;
private slots:
     void setValueObj();
     void cancelButtonPressed();
     void createButtonPressed();
     void editTypeSelect(int nb);
     void createSphere();

};

#else
    class MyPopup;

#endif // POPUP_H
