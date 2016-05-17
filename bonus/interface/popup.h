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
#include <QColorDialog>
#include <QLabel>
#include <QComboBox>
#include <object.h>
#include <QCheckBox>
#include <QSlider>
#include <qwidget.h>
#include <QFileDialog>
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
    void set_ui_selectobj();
    void set_ui_addobj();
    void set_ui_addmat();
    void set_layout_sphere(QGridLayout *mainLayout);
    void set_layout_mat(QGridLayout *mainLayout);
    int typeSelected = 0;
    /*
     * 0 : sphere
     */

private:
    QPushButton *Apply;
    QLabel *CenterX;
    QLabel *CenterY;
    QLabel *CenterZ;
    QLabel *matLab;
    QLabel *radLab;
    QLabel *reflectSlider;
    QLabel *transpaSlider;
    QLineEdit *EditRad;
    QLineEdit *EditX;
    QLineEdit *EditY;
    QLineEdit *EditZ;
    QLineEdit *EditName;
    QLineEdit *EditIor;
    QSlider *bumpstate;
    QLabel *LabelBump;
    QComboBox *matList;
    QSlider *transpa;
    QSlider *reflect;
    QCheckBox *sky;
    Object *object;
    MainWindow *mw;
    QComboBox *SelectMat;
    QPushButton *createSph;
    QPushButton *createMat;
    QPushButton *PrevColor;
    QPushButton *getPath;
    QLineEdit *curPath;
    QColorDialog *cp;
    QString path_file;
    Color ColorCur = Color();

private slots:
     void setValueObj();
     void cancelButtonPressed();
     void createButtonPressed();
     void editTypeSelect(int nb);
     void createSphere();
     void createMaterial();
     void EditSliderReflect(int nb);
     void EditSliderTranspa(int nb);
     void openColorPicker();
     void updatePrevButton(QColor);
     void selectPathFile();

};

#else
    class MyPopup;

#endif // POPUP_H
