#include "mainwindow.h"
#include "popup.h"
#include <qwidget.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QOpenGLWidget>
#include "sphere.h"

MyPopup::MyPopup() : QWidget()
{

}

MyPopup::~MyPopup()
{

}

void MyPopup::show_it()
{
    this->show();
}

void MyPopup::set_ui_obj(Object *object)
{
    QWidget *mainwindow = this;
    QWidget *window = new QWidget();
    if (object->getObjectType() == QString("sphere"))
    {
        QLabel *CenterX = new QLabel("Center x :\n", window);
        QLabel *CenterY = new QLabel("Center y :\n", window);
        QLabel *CenterZ = new QLabel("Center z :\n", window);
        QLineEdit *EditX = new QLineEdit();
        QLineEdit *EditY = new QLineEdit();
        QLineEdit *EditZ = new QLineEdit();
        QGridLayout *layout = new QGridLayout;
        QGridLayout *mainLayout = new QGridLayout;
        layout->addWidget(CenterX, 0, 0);
        layout->addWidget(CenterY, 1, 0);
        layout->addWidget(CenterZ, 2, 0);
        layout->addWidget(EditX, 0, 1);
        layout->addWidget(EditY, 1, 1);
        layout->addWidget(EditZ, 2, 1);
        window->setLayout(layout);
        window->setFixedSize(165, 150);
        mainLayout->addWidget(window);
        mainwindow->setLayout(mainLayout);
        mainwindow->setFixedWidth(600);

        EditX->setText(QString::number(object->center.x));
        EditY->setText(QString::number(object->center.y));
        EditZ->setText(QString::number(object->center.z));
        mainwindow->show();
    }
}

void MyPopup::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
