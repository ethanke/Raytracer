#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include "myxml.h"
#include "scene.h"
#include "color.h"

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
