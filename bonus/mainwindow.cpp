#include <QLineEdit>
#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_wx->setReadOnly(true);
    ui->lineEdit_wy->setReadOnly(true);
    ui->lineEdit_cpx->setReadOnly(true);
    ui->lineEdit_cpy->setReadOnly(true);
    ui->lineEdit_cpz->setReadOnly(true);
    ui->lineEdit_lax->setReadOnly(true);
    ui->lineEdit_lay->setReadOnly(true);
    ui->lineEdit_laz->setReadOnly(true);
    ui->lineEdit_fov->setReadOnly(true);
    ui->lineEdit_aa->setReadOnly(true);
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
    global_scene = new Scene(this);
    ui->lineEdit_wx->setReadOnly(false);
    ui->lineEdit_wy->setReadOnly(false);
    ui->lineEdit_cpx->setReadOnly(false);
    ui->lineEdit_cpy->setReadOnly(false);
    ui->lineEdit_cpz->setReadOnly(false);
    ui->lineEdit_lax->setReadOnly(false);
    ui->lineEdit_lay->setReadOnly(false);
    ui->lineEdit_laz->setReadOnly(false);
    ui->lineEdit_fov->setReadOnly(false);
    ui->lineEdit_aa->setReadOnly(false);
    ui->lineEdit_wx->setValidator( new QIntValidator(-900, 1920, this));
    ui->lineEdit_wy->setValidator( new QIntValidator(0, 1080, this));
    ui->lineEdit_cpx->setValidator( new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_cpy->setValidator( new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_cpz->setValidator( new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_lax->setValidator( new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_lay->setValidator( new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_laz->setValidator( new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_fov->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_aa->setValidator( new QIntValidator(1, 32, this));
    ui->lineEdit_wx->setText(QString::number(global_scene->camera->win_size.x));
    ui->lineEdit_wy->setText(QString::number(global_scene->camera->win_size.y));
    ui->lineEdit_cpx->setText(QString::number(global_scene->camera->start.x));
    ui->lineEdit_cpy->setText(QString::number(global_scene->camera->start.y));
    ui->lineEdit_cpz->setText(QString::number(global_scene->camera->start.z));
    ui->lineEdit_lax->setText(QString::number(global_scene->camera->look_at.x));
    ui->lineEdit_lay->setText(QString::number(global_scene->camera->look_at.y));
    ui->lineEdit_laz->setText(QString::number(global_scene->camera->look_at.z));
    ui->lineEdit_fov->setText(QString::number(global_scene->camera->fov.x));
    ui->lineEdit_aa->setText(QString::number(global_scene->camera->alliasing));

}


void MainWindow::on_lineEdit_wx_editingFinished()
{
    if (ui->lineEdit_wx->text() != NULL)
    global_scene->camera->win_size.x = ui->lineEdit_wx->text().toFloat();
}

void MainWindow::on_lineEdit_wy_editingFinished()
{
    if (ui->lineEdit_wy->text() != NULL)
    global_scene->camera->win_size.y = ui->lineEdit_wy->text().toFloat();
}

void MainWindow::on_lineEdit_cpx_editingFinished()
{
    if (ui->lineEdit_cpx->text() != NULL)
    global_scene->camera->start.x = ui->lineEdit_cpx->text().toFloat();
}

void MainWindow::on_lineEdit_cpy_editingFinished()
{
    if (ui->lineEdit_cpy->text() != NULL)
    global_scene->camera->start.y = ui->lineEdit_cpy->text().toFloat();
}

void MainWindow::on_lineEdit_cpz_editingFinished()
{
    if (ui->lineEdit_cpz->text() != NULL)
    global_scene->camera->start.z = ui->lineEdit_cpz->text().toFloat();
}

void MainWindow::on_lineEdit_lax_editingFinished()
{
    if (ui->lineEdit_lax->text() != NULL)
    global_scene->camera->look_at.x = ui->lineEdit_lax->text().toFloat();
}

void MainWindow::on_lineEdit_lay_editingFinished()
{
    if (ui->lineEdit_lay->text() != NULL)
    global_scene->camera->look_at.y = ui->lineEdit_lay->text().toFloat();
}

void MainWindow::on_lineEdit_laz_editingFinished()
{
    if (ui->lineEdit_laz->text() != NULL)
    global_scene->camera->look_at.z = ui->lineEdit_laz->text().toFloat();
}

void MainWindow::on_lineEdit_aa_editingFinished()
{
    if (ui->lineEdit_aa->text() != NULL)
    global_scene->camera->alliasing = ui->lineEdit_aa->text().toFloat();
}

void MainWindow::on_lineEdit_fov_editingFinished()
{
    if (ui->lineEdit_fov->text() != NULL)
    global_scene->camera->fov.x = ui->lineEdit_fov->text().toFloat();
}
