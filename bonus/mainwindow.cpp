#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::CloseWindow()
{
    close();
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
    this->scene = new Scene(this);
    if (this->scene->stringlist.length() != 0)
    {
        this->xml_file = new MyXML(this->scene->stringlist);
        qDebug() << this->xml_file->get_field("scene:view:x_size");
    }
}
