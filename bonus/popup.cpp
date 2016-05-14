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

void MyPopup::set_ui_addobj()
{
    QWidget *mainwindow = this;
    QGridLayout *layout = new QGridLayout;
    QGridLayout *mainLayout = new QGridLayout;
    if (this->typeSelected == 0)
        set_layout_sphere(mainLayout);
    this->set_layout_sphere(mainLayout);
    mainwindow->setLayout(mainLayout);
    mainwindow->setFixedWidth(600);
    mainwindow->setFixedHeight(400);
    if (this->typeSelected == 0)
     QObject::connect(this->createSph, SIGNAL(clicked(bool)), this, SLOT(createSphere()));
    mainwindow->show();
}

void MyPopup::set_layout_sphere(QGridLayout *mainLayout)
{
    QLabel *LabelX = new QLabel("Center X :");
    QLabel *LabelY = new QLabel("Center Y :");
    QLabel *LabelZ = new QLabel("Center Z :");
    QLabel *LabelRad = new QLabel("Radius :");
    QLabel *LabelMat = new QLabel("Material :");
    this->EditX = new QLineEdit();
    this->EditY = new QLineEdit();
    this->EditZ = new QLineEdit();
    this->EditRad = new QLineEdit();
    this->SelectMat = new QComboBox();
    this->createSph = new QPushButton("Create");
    if (!global_scene->matCount)
        this->SelectMat->addItem(QString("No material found"));
    else
        for (int i = 0; i != global_scene->matCount; i++)
            this->SelectMat->addItem(QString("Matériaux n°" + QString::number(i)));
    mainLayout->addWidget(LabelX, 0, 0);
    mainLayout->addWidget(this->EditX, 0, 1);
    mainLayout->addWidget(LabelY, 1, 0);
    mainLayout->addWidget(this->EditY, 1, 1);
    mainLayout->addWidget(LabelZ, 2, 0);
    mainLayout->addWidget(this->EditZ, 2, 1);
    mainLayout->addWidget(LabelRad, 3, 0);
    mainLayout->addWidget(this->EditRad, 3, 1);
    mainLayout->addWidget(LabelMat, 4, 0);
    mainLayout->addWidget(this->SelectMat, 4, 1);
    mainLayout->addWidget(this->createSph, 5, 1);
}

void MyPopup::createSphere()
{
    Sphere *sphere = new Sphere(Vector3f<float>(this->EditX->text().toFloat(),
                         this->EditY->text().toFloat(),
                         this->EditZ->text().toFloat()),
                this->EditRad->text().toFloat(),
                global_scene->matList.at(this->SelectMat->currentIndex()));
    global_scene->objectList.push_back(sphere);
    global_scene->objectCount += 1;
    this->mw->refObjTab();
     this->destroy();
}

void MyPopup::set_ui_selectobj()
{
    QWidget *mainwindow = this;
    QLabel *typeLabel = new QLabel("Type :\n");
    QComboBox *typeSelect = new QComboBox();
    QGridLayout *layout = new QGridLayout;
    QGridLayout *mainLayout = new QGridLayout;
    QPushButton *createButton = new QPushButton("Create");
    QPushButton *cancelButton = new QPushButton("Cancel");
    typeSelect->addItem("Sphere");
    typeSelect->addItem("Plan");
    mainLayout->addWidget(typeLabel, 0, 0);
    mainLayout->addWidget(typeSelect, 0, 1);
    mainLayout->addWidget(createButton, 1, 0);
    mainLayout->addWidget(cancelButton, 1, 1);
    mainwindow->setLayout(mainLayout);
    mainwindow->setFixedWidth(300);
    mainwindow->setFixedHeight(100);
    QObject::connect(typeSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(editTypeSelect(int)));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPressed()));
    QObject::connect(createButton, SIGNAL(clicked()), this, SLOT(createButtonPressed()));
    mainwindow->show();
}

void MyPopup::cancelButtonPressed()
{
    this->destroy(true);
}

void MyPopup::editTypeSelect(int nb)
{
   this->typeSelected = nb;
}

void MyPopup::createButtonPressed()
{
    MyPopup *popup = new MyPopup(this->mw);
    popup->set_ui_addobj();
    this->destroy();
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
    }
    mainwindow->show();
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
