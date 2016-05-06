#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "addobjectpopup.h"
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    int CloseWindow();
    void show_pop();

private slots:
    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H