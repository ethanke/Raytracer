#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLineEdit>
#include "myxml.h"
#include "scene.h"
#include "color.h"
#include "global.h"

namespace Ui {
class MainWindow;
}

extern Color *pixel_buff;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Scene *scene;
    MyXML *xml_file;

protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    void CloseWindow();

private slots:
    void on_loadButton_clicked();


    void on_lineEdit_wx_editingFinished();

    void on_lineEdit_wy_editingFinished();

    void on_lineEdit_cpx_editingFinished();

    void on_lineEdit_cpy_editingFinished();

    void on_lineEdit_cpz_editingFinished();

    void on_lineEdit_lax_editingFinished();

    void on_lineEdit_lay_editingFinished();

    void on_lineEdit_laz_editingFinished();

    void on_lineEdit_aa_editingFinished();

    void on_lineEdit_fov_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
