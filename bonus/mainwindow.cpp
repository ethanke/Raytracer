#include <QLineEdit>
#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "popup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cpx->setReadOnly(true);
    ui->lineEdit_cpy->setReadOnly(true);
    ui->lineEdit_cpz->setReadOnly(true);
    ui->lineEdit_lax->setReadOnly(true);
    ui->lineEdit_lay->setReadOnly(true);
    ui->lineEdit_laz->setReadOnly(true);
    ui->comboBox_wx->setDisabled(true);
    ui->comboBox_wy->setDisabled(true);
    ui->horizontalSlider_aa->setDisabled(true);
    ui->horizontalSlider_fov->setDisabled(true);
    ui->listObject->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listObject->setColumnWidth(0, ui->listObject->size().width());
    ui->listObject->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listLight->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listLight->setColumnWidth(0, ui->listLight->size().width());
    ui->listLight->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listMat->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listMat->setColumnWidth(0, ui->listMat->size().width());
    ui->listMat->setSelectionMode(QAbstractItemView::SingleSelection);
    QString tab_x[] = {"1152", "960", "768", "640", "576", "480", "384", "320"};
    QString tab_y[] = {"720", "600", "480", "400", "360", "300", "240", "300"};
    for(int i = 0; i < 8; i++)
      ui->comboBox_wx->addItem(tab_x[i]);
    for(int i = 0; i < 8; i++)
      ui->comboBox_wy->addItem(tab_y[i]);
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
    ui->lineEdit_cpx->setReadOnly(false);
    ui->lineEdit_cpy->setReadOnly(false);
    ui->lineEdit_cpz->setReadOnly(false);
    ui->lineEdit_lax->setReadOnly(false);
    ui->lineEdit_lay->setReadOnly(false);
    ui->lineEdit_laz->setReadOnly(false);
    ui->comboBox_wx->setDisabled(false);
    ui->comboBox_wy->setDisabled(false);
    ui->horizontalSlider_aa->setDisabled(false);
    ui->horizontalSlider_fov->setDisabled(false);
    ui->lineEdit_cpx->setValidator(new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_cpy->setValidator(new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_cpz->setValidator(new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_lax->setValidator(new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_lay->setValidator(new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_laz->setValidator(new QIntValidator(-99999999, 99999999, this));
    ui->lineEdit_cpx->setText(QString::number(global_scene->camera->start.x));
    ui->lineEdit_cpy->setText(QString::number(global_scene->camera->start.y));
    ui->lineEdit_cpz->setText(QString::number(global_scene->camera->start.z));
    ui->lineEdit_lax->setText(QString::number(global_scene->camera->look_at.x));
    ui->lineEdit_lay->setText(QString::number(global_scene->camera->look_at.y));
    ui->lineEdit_laz->setText(QString::number(global_scene->camera->look_at.z));
    int i = 0;
    while (i < int(global_scene->matList.size()))
    {
        ui->listMat->insertRow(i);
        ui->listMat->setItem(i, 0, new QTableWidgetItem(QString::number(global_scene->matList[i]->color->r * 255), 1));
        i++;
    }
    i = 0;
    while (i < int(global_scene->objectList.size()))
    {
        ui->listObject->insertRow(i);
        ui->listObject->setItem(i, 0, new QTableWidgetItem(QString::number(global_scene->objectList[i]->center.x), 1));
        i++;
    }
    i = 0;
    while (i < global_scene->lightCount)
    {
        ui->listLight->insertRow(i);
        ui->listLight->setItem(i, 0, new QTableWidgetItem(QString::number(global_scene->lightList[i]->intensity), 1));
        i++;
    }
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

void MainWindow::on_comboBox_wx_currentIndexChanged(const QString &arg1)
{
    if (global_scene != NULL)
        global_scene->camera->win_size.x = arg1.toInt();
}

void MainWindow::on_comboBox_wy_currentIndexChanged(const QString &arg1)
{
    if (global_scene != NULL)
        global_scene->camera->win_size.y = arg1.toInt();
}


void MainWindow::on_horizontalSlider_aa_valueChanged(int value)
{
   ui->LabelAA->setText(QString::number(value).toLatin1().data());
   global_scene->camera->alliasing = value;
}

void MainWindow::on_horizontalSlider_fov_valueChanged(int value)
{
    ui->labelFOV->setText(QString::number(value));
    global_scene->camera->update_fov(float(value));
}

void MainWindow::on_listObject_itemClicked(QTableWidgetItem *item)
{
    this->objSelect = item->row();
}

void MainWindow::on_editButtonObj_clicked()
{
    if (this->objSelect != 0)
    {
       Popup *popup = new Popup();
       popup->show();
       popup->set_ui_obj();
    }
}
