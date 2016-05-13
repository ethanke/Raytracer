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
        this->CenterX = new QLabel("Center x :\n", window);
        this->CenterY = new QLabel("Center y :\n", window);
        this->CenterZ = new QLabel("Center z :\n", window);
        this->EditX = new QLineEdit();
        this->EditY = new QLineEdit();
        this->EditZ = new QLineEdit();
        this->Apply = new QPushButton();
        QGridLayout *layout = new QGridLayout;
        QGridLayout *mainLayout = new QGridLayout;
        layout->addWidget(CenterX, 0, 0);
        layout->addWidget(CenterY, 1, 0);
        layout->addWidget(CenterZ, 2, 0);
        layout->addWidget(EditX, 0, 1);
        layout->addWidget(EditY, 1, 1);
        layout->addWidget(EditZ, 2, 1);
        layout->addWidget(Apply, 4, 1);
        window->setLayout(layout);
        window->setFixedSize(165, 150);
        mainLayout->addWidget(window);
        mainwindow->setLayout(mainLayout);
        mainwindow->setFixedWidth(600);
        this->Apply->setText(QString("Apply"));
        QObject::connect(this->Apply, SIGNAL(clicked()), this, SLOT(setValueObj()));
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

void MyPopup::setValueObj()
{
    int i = 0;
    object->center.x = this->EditX->text().toFloat();
    object->center.y = this->EditY->text().toFloat();
    object->center.z = this->EditZ->text().toFloat();

    this->mw->affObjTab();
}
