#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addobjectpopup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

int MainWindow::CloseWindow()
{
    exit(1);
}

void MainWindow::show_pop()
{
    addObjectPopup *pop = new addObjectPopup;
    pop->show_it();
}

MainWindow::~MainWindow()
{
    delete ui;
}


