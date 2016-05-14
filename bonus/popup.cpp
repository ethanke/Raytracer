#include "popup.h"

MyPopup::MyPopup(MainWindow *mw)
{
    this->mw = mw;
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
    this->object = object;
    if (object->getObjectType() == QString("sphere"))
    {
        Sphere *sphere = static_cast <Sphere *>(object);
        this->CenterX = new QLabel("Center x :\n", window);
        this->CenterY = new QLabel("Center y :\n", window);
        this->CenterZ = new QLabel("Center z :\n", window);
        this->matLab = new QLabel("Matériaux :", window);
        this->radLab = new QLabel("Radius :", window);
        this->EditX = new QLineEdit();
        this->EditY = new QLineEdit();
        this->EditZ = new QLineEdit();
        this->Apply = new QPushButton();
        this->matList = new QComboBox();
        this->EditRad = new QLineEdit();
        QGridLayout *layout = new QGridLayout;
        QGridLayout *mainLayout = new QGridLayout;
        layout->addWidget(CenterX, 0, 0);
        layout->addWidget(CenterY, 1, 0);
        layout->addWidget(CenterZ, 2, 0);
        layout->addWidget(EditX, 0, 1);
        layout->addWidget(EditY, 1, 1);
        layout->addWidget(EditZ, 2, 1);
        layout->addWidget(matLab, 3, 0);
        layout->addWidget(matList, 3, 1);
        layout->addWidget(radLab, 4, 0);
        layout->addWidget(EditRad, 4, 1);
        layout->addWidget(Apply, 5, 1);
        QString *tab = new QString();
        int i = 0;
        while (i != global_scene->matCount)
        {
            this->matList->addItem(QString("Matériaux n°" + QString::number(i)));
            i++;
        }
        this->matList->setCurrentIndex(object->material->id - 1);
        window->setLayout(layout);
        window->setFixedSize(220, 280);
        mainLayout->addWidget(window);
        mainwindow->setLayout(mainLayout);
        mainwindow->setFixedWidth(600);
        mainwindow->setFixedHeight(400);
        this->Apply->setText(QString("Apply"));
        QObject::connect(this->Apply, SIGNAL(clicked()), this, SLOT(setValueObj()));
        EditX->setText(QString::number(object->center.x));
        EditY->setText(QString::number(object->center.y));
        EditZ->setText(QString::number(object->center.z));
        EditRad->setText(QString::number(sphere->radius));
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

void MyPopup::setValueObj()
{
    Sphere *sphere = static_cast <Sphere *>(this->object);
    int i = 0;
    object->center.x = this->EditX->text().toFloat();
    object->center.y = this->EditY->text().toFloat();
    object->center.z = this->EditZ->text().toFloat();
    object->material = global_scene->matList[this->matList->currentIndex()];
    sphere->radius = this->EditRad->text().toFloat();
    this->mw->refObjTab();
}
