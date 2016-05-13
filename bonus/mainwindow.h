#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <qtablewidget.h>
#include <QKeyEvent>
#include <QLineEdit>
#include "popup.h"
#include "myxml.h"
#include "popup.h"
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
    int objSelect = -1;
    MyPopup *popup;
    void affObjTab();
    void affMatTab();
    void affLightTab();

    MyXML *xml_file;

protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    void CloseWindow();

private slots:

    void on_loadButton_clicked();


    void on_lineEdit_cpx_editingFinished();

    void on_lineEdit_cpy_editingFinished();

    void on_lineEdit_cpz_editingFinished();

    void on_lineEdit_lax_editingFinished();

    void on_lineEdit_lay_editingFinished();

    void on_lineEdit_laz_editingFinished();

    void on_comboBox_wx_currentIndexChanged(const QString &arg1);

    void on_comboBox_wy_currentIndexChanged(const QString &arg1);

    void on_horizontalSlider_aa_valueChanged(int value);

    void on_horizontalSlider_fov_valueChanged(int value);

    void on_listObject_itemClicked(QTableWidgetItem *item);

    void on_editButtonObj_clicked();


    void on_pushButton_3_pressed();

private:
    Ui::MainWindow *ui;
};

#else
    class MainWindow;

#endif // MAINWINDOW_H
