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

void MyPopup::editMaterial()
{
    qDebug() << this->EditIor->text().toFloat();
    global_scene->matList[this->editId]->name = this->EditName->text();
    global_scene->matList[this->editId]->color = this->editColorCur;
    global_scene->matList[this->editId]->reflect = static_cast<float>(this->reflect->value()) / 100.0;
    global_scene->matList[this->editId]->transparency = static_cast<float>(this->transpa->value()) / 100.0;
    global_scene->matList[this->editId]->ior = this->EditIor->text().toFloat();
    global_scene->matList[this->editId]->bump = static_cast<float>(bumpstate->value()) / 100.0;
    global_scene->matList[this->editId]->updateIor(this->EditIor->text().toInt());
    global_scene->matList[this->editId]->sky = this->sky->isChecked();
    global_scene->matList[this->editId]->updateImage(this->path_file);

            /*
            global_scene->matList.at(this->editId) = new Material(this->EditName->text(),
                                      int(global_scene->matList.size()) + 1,
                                      this->ColorCur,
                                      this->reflect->value(),
                                      this->transpa->value(),
                                      this->EditIor->text().toInt(),
                                      static_cast<float>(this->bumpstate->value()) / 100.0,
                                      this->sky->isChecked(),
                                      this->path_file);
            */
    this->mw->refMatTab();
    this->destroy();
    /*
     *  transpa; 0 à 100%
     * reflect; 0 à 100%
     * ior; entre 1 et infine
     * bump; float entre 0 et 1
     * sky; booléen (true / false)
     * path; chemin de la texture
     * Material::Material(const int id, const Color color, const float reflect,
     *
     *  const float transparency, const float ior, const float bump, const int sky, QString path)
     */
}

void MyPopup::createMaterial()
{
    Material *material = new Material(this->EditName->text(),
                                      int(global_scene->matList.size()) + 1,
                                      this->ColorCur,
                                      this->reflect->value(),
                                      this->transpa->value(),
                                      this->EditIor->text().toFloat(),
                                      static_cast<float>(this->bumpstate->value()) / 100.0,
                                      this->sky->isChecked(),
                                      this->path_file);
    qDebug() << material->bump;
    global_scene->matList.push_back(material);
    global_scene->matCount += 1;
    this->mw->refMatTab();
    this->destroy();
    /*
     *  transpa; 0 à 100%
     * reflect; 0 à 100%
     * ior; entre 1 et infine
     * bump; float entre 0 et 1
     * sky; booléen (true / false)
     * path; chemin de la texture
     * Material::Material(const int id, const Color color, const float reflect,
     *
     *  const float transparency, const float ior, const float bump, const int sky, QString path)
     */
}

void MyPopup::set_ui_addmat()
{
    QWidget *mainwindow = this;
    QGridLayout *mainLayout = new QGridLayout;
    this->set_layout_mat(mainLayout);
    mainwindow->setLayout(mainLayout);
    mainwindow->setFixedWidth(600);
    mainwindow->setFixedHeight(400);
    mainwindow->show();
}

void MyPopup::set_ui_editmat(int id)
{
    QWidget *mainwindow = this;
    QGridLayout *mainLayout = new QGridLayout;
    this->editId = id;
    this->set_layout_editmat(mainLayout, id);
    mainwindow->setLayout(mainLayout);
    mainwindow->setFixedWidth(600);
    mainwindow->setFixedHeight(400);
    mainwindow->show();
}

void MyPopup::selectPathFile()
{
   this->path_file = QFileDialog::getOpenFileName(this, QObject::tr("Open File"),"/path/to/file/", QObject::tr("Files png's only (*.png)"));
   this->curPath->setText(this->path_file);
}

void MyPopup::set_layout_mat(QGridLayout *mainLayout)
{
    QLabel *LabelName = new QLabel("Name :");
    QLabel *LabelColor = new QLabel("Color :");
    QLabel *LabelTra = new QLabel("Transparence :");
    QLabel *LabelIor = new QLabel("Ior (indice of refraction) :");
    QLabel *LabelBum = new QLabel("Bump :");
    QLabel *LabelReflect = new QLabel("Reflection :");
    QLabel *LabelSky = new QLabel("Is Skybox ? ");
    this->PrevColor = new QPushButton();
    this->PrevColor->setStyleSheet("background-color:rgba( 35, 35, 35, 0%);"
                                      "border-style: outset;"
                                        "border-width: 2px;"
                                        "border-color: black");
    this->path_file = QString("No file");
    this->EditIor = new QLineEdit();
    this->EditName = new QLineEdit();
    this->createMat = new QPushButton("Create");
    this->getPath = new QPushButton("Choose file");
    this->curPath = new QLineEdit();
    this->curPath->setDisabled(true);
    this->curPath->setText(this->path_file);
    this->curPath->setModified(false);
    this->bumpstate = new QSlider();
    this->bumpstate->setOrientation(Qt::Horizontal);
    this->bumpstate->setMaximum(100);
    this->LabelBump = new QLabel("0.00");
    connect(this->bumpstate, SIGNAL(sliderMoved(int)), this, SLOT(EditSliderBump(int)));
    this->reflect = new QSlider();
    this->reflectSlider = new QLabel("0%");
    this->reflect->setOrientation(Qt::Horizontal);
    this->reflect->setMaximum(100);
    connect(this->reflect, SIGNAL(sliderMoved(int)), this, SLOT(EditSliderReflect(int)));
    this->transpa = new QSlider();
    this->transpaSlider = new QLabel("0%");
    this->transpa->setOrientation(Qt::Horizontal);
    this->transpa->setMaximum(100);
    connect(this->transpa, SIGNAL(sliderMoved(int)), this, SLOT(EditSliderTranspa(int)));
    this->sky = new QCheckBox();
    this->EditIor->setValidator(new QIntValidator(0, 99999999, this));
    this->EditIor->setPlaceholderText("0 for disable");
    connect(this->PrevColor, SIGNAL(clicked(bool)), this, SLOT(openColorPicker()));
    this->cp = new QColorDialog();
    connect(this->cp, SIGNAL(colorSelected(QColor)), this, SLOT(updatePrevButton(QColor)));
    connect(this->createMat, SIGNAL(clicked(bool)), this, SLOT(createMaterial()));
    connect(this->getPath, SIGNAL(clicked(bool)), this, SLOT(selectPathFile()));
    mainLayout->addWidget(LabelName, 0, 0);
    mainLayout->addWidget(EditName, 0, 1);
    mainLayout->addWidget(LabelColor, 1, 0);
    mainLayout->addWidget(PrevColor, 1, 1);
    mainLayout->addWidget(LabelReflect, 2, 0);
    mainLayout->addWidget(reflectSlider, 3, 0);
    mainLayout->addWidget(reflect, 3, 1);
    mainLayout->addWidget(LabelTra, 4, 0);
    mainLayout->addWidget(transpaSlider, 5, 0);
    mainLayout->addWidget(transpa, 5, 1);
    mainLayout->addWidget(LabelIor, 6, 0);
    mainLayout->addWidget(EditIor, 6, 1);
    mainLayout->addWidget(LabelBum, 7, 0);
    mainLayout->addWidget(LabelBump, 8, 0);
    mainLayout->addWidget(bumpstate, 8, 1);
    mainLayout->addWidget(createMat, 11, 1);
    mainLayout->addWidget(LabelSky, 9, 0);
    mainLayout->addWidget(sky, 9, 1);
    mainLayout->addWidget(getPath, 10, 0);
    mainLayout->addWidget(curPath, 10, 1);
}

void MyPopup::set_layout_editmat(QGridLayout *mainLayout, int id)
{
    QLabel *LabelName = new QLabel("Name :");
    QLabel *LabelColor = new QLabel("Color :");
    QLabel *LabelTra = new QLabel("Transparence :");
    QLabel *LabelIor = new QLabel("Ior (indice of refraction) :");
    QLabel *LabelBum = new QLabel("Bump :");
    QLabel *LabelReflect = new QLabel("Reflection :");
    QLabel *LabelSky = new QLabel("Is Skybox ? ");
    this->PrevColor = new QPushButton();
    this->editColorCur = global_scene->matList[id]->color; // new Color(global_scene->matList[id]->color->r, global_scene->matList[id]->color->r, global_scene->matList[id]->color->b);
    this->PrevColor->setStyleSheet("background-color:rgba(" + QString::number(global_scene->matList[id]->color->r * 255) + "," + QString::number(global_scene->matList[id]->color->g * 255) + "," +
                                   QString::number(global_scene->matList[id]->color->b * 255) + ", 100%);"
                                   "border-style: outset;"
                                   "border-width: 2px;"
                                   "border-color: black");
    this->path_file = QString("No file");
    this->EditIor = new QLineEdit();
    this->EditName = new QLineEdit();
    this->editMat = new QPushButton("Edit");
    this->getPath = new QPushButton("Choose file");
    this->curPath = new QLineEdit();
    this->curPath->setDisabled(true);
    this->curPath->setText(this->path_file);
    this->curPath->setModified(false);
    this->bumpstate = new QSlider();
    this->bumpstate->setOrientation(Qt::Horizontal);
    this->bumpstate->setMaximum(100);
    this->LabelBump = new QLabel("0.00");
    connect(this->bumpstate, SIGNAL(sliderMoved(int)), this, SLOT(EditSliderBump(int)));
    this->reflect = new QSlider();
    this->reflectSlider = new QLabel("0%");
    this->reflect->setOrientation(Qt::Horizontal);
    this->reflect->setMaximum(100);
    connect(this->reflect, SIGNAL(sliderMoved(int)), this, SLOT(EditSliderReflect(int)));
    this->transpa = new QSlider();
    this->transpaSlider = new QLabel("0%");
    this->transpa->setOrientation(Qt::Horizontal);
    this->transpa->setMaximum(100);
    connect(this->transpa, SIGNAL(sliderMoved(int)), this, SLOT(EditSliderTranspa(int)));
    this->sky = new QCheckBox();
    this->EditIor->setValidator(new QDoubleValidator(0, 5, 5, this));
    this->EditIor->setPlaceholderText("0 for disable");
    connect(this->PrevColor, SIGNAL(clicked(bool)), this, SLOT(openColorPicker()));
    this->cp = new QColorDialog();
    connect(this->cp, SIGNAL(colorSelected(QColor)), this, SLOT(updatePrevButton(QColor)));
    connect(this->editMat, SIGNAL(clicked(bool)), this, SLOT(editMaterial()));
    connect(this->getPath, SIGNAL(clicked(bool)), this, SLOT(selectPathFile()));
    mainLayout->addWidget(LabelName, 0, 0);
    this->EditName->setText(global_scene->matList[id]->name);
    mainLayout->addWidget(EditName, 0, 1);
    mainLayout->addWidget(LabelColor, 1, 0);
    this->PrevColor->update();
    mainLayout->addWidget(PrevColor, 1, 1);
    mainLayout->addWidget(LabelReflect, 2, 0);
    this->reflectSlider->setText(QString::number(global_scene->matList[id]->reflect * 100) + "%");
    mainLayout->addWidget(reflectSlider, 3, 0);
    this->reflect->setValue(global_scene->matList[id]->reflect * 100);
    mainLayout->addWidget(reflect, 3, 1);
    mainLayout->addWidget(LabelTra, 4, 0);
    this->transpaSlider->setText(QString::number(global_scene->matList[id]->transparency * 100) + "%");
    mainLayout->addWidget(transpaSlider, 5, 0);
    this->transpa->setValue(global_scene->matList[id]->transparency * 100);
    mainLayout->addWidget(transpa, 5, 1);
    mainLayout->addWidget(LabelIor, 6, 0);
    this->EditIor->setText(QString::number(global_scene->matList[id]->ior == NULL ? 0 : global_scene->matList[id]->ior));
    mainLayout->addWidget(EditIor, 6, 1);
    this->LabelBump->setText(QString::number(global_scene->matList[id]->bump) + "%");
    mainLayout->addWidget(LabelBum, 7, 0);
    mainLayout->addWidget(LabelBump, 8, 0);
    this->bumpstate->setValue(global_scene->matList[id]->bump * 100);
    mainLayout->addWidget(bumpstate, 8, 1);
    mainLayout->addWidget(editMat, 11, 1);
    mainLayout->addWidget(LabelSky, 9, 0);
    this->sky->setChecked((global_scene->matList[id]->sky == 1) ? (true) : (false));
    mainLayout->addWidget(sky, 9, 1);
    mainLayout->addWidget(getPath, 10, 0);
    //this->curPath->setText(global_scene->matList[id]->path);
    mainLayout->addWidget(curPath, 10, 1);
}

void MyPopup::updatePrevButton(QColor color)
{
    this->PrevColor->setStyleSheet("background-color:rgba( 35, 35, 35, 0%);"
                                      "border-style: outset;"
                                        "border-width: 2px;"
                                        "border-color: black");
    this->ColorCur = Color(color.redF(), color.greenF(), color.blueF());
    this->editColorCur = new Color(color.redF(), color.greenF(), color.blueF());
    QPalette pal = this->PrevColor->palette();
    pal.setColor(QPalette::Button, QColor(color));
    QBrush tb(Qt::transparent);
    this->PrevColor->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    this->PrevColor->setAutoFillBackground(true);
    this->PrevColor->setPalette(pal);
    this->PrevColor->update();
}

void MyPopup::openColorPicker()
{
    cp->show();
}
void MyPopup::EditSliderBump(int nb)
{
    this->LabelBump->setText(QString::number((nb) / 100.0));
}

void MyPopup::EditSliderReflect(int nb)
{
    this->reflectSlider->setText(QString::number(nb) + "%");
}

void MyPopup::EditSliderTranspa(int nb)
{
    this->transpaSlider->setText(QString::number(nb) + "%");
}

void MyPopup::set_ui_addobj()
{
    QWidget *mainwindow = this;
    QGridLayout *mainLayout = new QGridLayout;
    if (this->typeSelected == 0)
      this->set_layout_sphere(mainLayout);
    mainwindow->setLayout(mainLayout);
    mainwindow->setFixedWidth(600);
    mainwindow->setFixedHeight(400);
    if (this->typeSelected == 0)
     QObject::connect(this->createSph, SIGNAL(clicked(bool)), this, SLOT(createMaterial()));
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
    this->EditX->setValidator(new QIntValidator(-99999999, 99999999, this));
    this->EditY->setValidator(new QIntValidator(-99999999, 99999999, this));
    this->EditZ->setValidator(new QIntValidator(-99999999, 99999999, this));
    this->EditRad->setValidator(new QIntValidator(-99999999, 99999999, this));
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
    typeSelect->addItem("Cylindre");
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
        this->EditX->setValidator(new QIntValidator(-99999999, 99999999, this));
        this->EditY->setValidator(new QIntValidator(-99999999, 99999999, this));
        this->EditZ->setValidator(new QIntValidator(-99999999, 99999999, this));
        this->EditRad->setValidator(new QIntValidator(-99999999, 99999999, this));
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
        int i = 0;
        while (i != global_scene->matCount)
        {
            this->matList->addItem(global_scene->matList[i]->name);
            i++;
        }
        connect(this->matList, SIGNAL(activated(int)), this, SLOT(refMatListInObj(int)));
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
    if (object->getObjectType() == QString("Cylinder"))
    {
        Cylinder *cylinder = static_cast <Cylinder *>(object);
        this->CenterX = new QLabel("Center x :", window);
        this->CenterY = new QLabel("Center y :", window);
        this->CenterZ = new QLabel("Center z :", window);
        this->LabDir = new QLabel("Direction :", window);
        this->matLab = new QLabel("Matériaux :", window);
        this->radLab = new QLabel("Radius :", window);
        this->LabHeight = new QLabel("Height :", window);
        this->EditX = new QLineEdit();
        this->EditY = new QLineEdit();
        this->EditZ = new QLineEdit();
        this->DirX = new QLineEdit();
        this->DirY = new QLineEdit();
        this->DirZ = new QLineEdit();
        this->Height = new QLineEdit();
        this->Apply = new QPushButton();
        this->matList = new QComboBox();
        this->EditRad = new QLineEdit();
        this->EditX->setValidator(new QIntValidator(-99999999, 99999999, this));
        this->EditY->setValidator(new QIntValidator(-99999999, 99999999, this));
        this->EditZ->setValidator(new QIntValidator(-99999999, 99999999, this));
        this->DirX->setValidator(new QIntValidator(0, 1, this));
        this->DirY->setValidator(new QIntValidator(0, 1, this));
        this->DirZ->setValidator(new QIntValidator(0, 1, this));
        this->Height->setValidator(new QIntValidator(-99999999, 99999999, this));
        this->DirX->setPlaceholderText("0 (1 for activate)");
        this->DirY->setPlaceholderText("0 (1 for activate)");
        this->DirZ->setPlaceholderText("0 (1 for activate)");
        this->EditRad->setValidator(new QIntValidator(-99999999, 99999999, this));
        QGridLayout *layout = new QGridLayout;
        QGridLayout *mainLayout = new QGridLayout;
        layout->addWidget(CenterX, 0, 0);
        layout->addWidget(CenterY, 1, 0);
        layout->addWidget(CenterZ, 2, 0);
        layout->addWidget(EditX, 0, 1);
        layout->addWidget(EditY, 1, 1);
        layout->addWidget(EditZ, 2, 1);
        layout->addWidget(matLab, 7, 0);
        layout->addWidget(matList, 7, 1);
        layout->addWidget(radLab, 3, 0);
        layout->addWidget(EditRad, 3, 1);
        layout->addWidget(LabDir, 5, 0);
        layout->addWidget(DirX, 6, 0);
        layout->addWidget(DirY, 6, 1);
        layout->addWidget(DirZ, 6, 2);
        layout->addWidget(LabHeight, 4, 0);
        layout->addWidget(Height, 4, 1);
        layout->addWidget(Apply, 8, 1);
        int i = 0;
        while (i != global_scene->matCount)
        {
            this->matList->addItem(global_scene->matList[i]->name);
            i++;
        }
        connect(this->matList, SIGNAL(activated(int)), this, SLOT(refMatListInObj(int)));
        this->matList->setCurrentIndex(object->material->id - 1);
        window->setLayout(layout);
        window->setFixedSize(450, 280);
        mainLayout->addWidget(window);
        mainwindow->setLayout(mainLayout);
        mainwindow->setFixedWidth(600);
        mainwindow->setFixedHeight(400);
        this->Apply->setText(QString("Apply"));
        QObject::connect(this->Apply, SIGNAL(clicked()), this, SLOT(setValueObj()));
        EditX->setText(QString::number(object->center.x));
        EditY->setText(QString::number(object->center.y));
        EditZ->setText(QString::number(object->center.z));
        EditRad->setText(QString::number(cylinder->radius));
        Height->setText(QString::number(cylinder->height));
        DirX->setText(QString::number(cylinder->direction.x));
        DirY->setText(QString::number(cylinder->direction.y));
        DirZ->setText(QString::number(cylinder->direction.z));

        // Cylinder::Cylinder(const Vector3f<float> center, const Vector3f<float> direction,
        // const float radius, const float height, Material *mat)
    }
    mainwindow->show();
}

void MyPopup::refMatListInObj(int nb)
{
    int i = 0;
    while (this->matList->count() > 0)
        this->matList->removeItem(0);
    while (i != global_scene->matCount)
    {
        this->matList->addItem(global_scene->matList[i]->name);
        i++;
    }
    this->matList->setCurrentIndex(nb);
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
    if (this->object->getObjectType() == QString("sphere"))
    {
        Sphere *sphere = static_cast <Sphere *>(this->object);
        int i = 0;
        object->center.x = this->EditX->text().toFloat();
        object->center.y = this->EditY->text().toFloat();
        object->center.z = this->EditZ->text().toFloat();
        object->material = global_scene->matList[this->matList->currentIndex()];
        sphere->radius = this->EditRad->text().toFloat();
    }
    if (this->object->getObjectType() == QString("Cylinder"))
    {
        Cylinder *cylinder = static_cast <Cylinder *>(this->object);
        int i = 0;
        object->center.x = this->EditX->text().toFloat();
        object->center.y = this->EditY->text().toFloat();
        object->center.z = this->EditZ->text().toFloat();
        object->material = global_scene->matList[this->matList->currentIndex()];
        cylinder->radius = this->EditRad->text().toFloat();
        cylinder->height = this->Height->text().toFloat();
        cylinder->direction.x = this->DirX->text().toFloat();
        cylinder->direction.y = this->DirY->text().toFloat();
        cylinder->direction.z = this->DirZ->text().toFloat();
    }
    this->mw->refObjTab();
    this->destroy();
}
