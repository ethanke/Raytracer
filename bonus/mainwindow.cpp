#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <string.h>
#include <qdom.h>
#include <QDebug>

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::on_loadButton_clicked()
{
    Scene *scene = new Scene();
    scene->path_file = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("Files Xml's only (*.xml)"));
    scene->file = new QFile(scene->path_file);
    QStringList myStringList;

    if (!scene->file->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "Error opening file", scene->file->errorString());
    }
    else
    {
        while(!scene->file->atEnd())
        {
            myStringList.append(scene->file->readLine());
        }

        scene->file->close();
    }
}
