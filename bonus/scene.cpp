#include "scene.h"
#include "sphere.h"
#include <qdebug.h>

Scene::Scene(QWidget *parent)
{
    this->path_file = QFileDialog::getOpenFileName(parent, QObject::tr("Open File"),"/path/to/file/", QObject::tr("Files Xml's only (*.xml)"));
    this->file = new QFile(this->path_file);
    QStringList myStringList;

    if (!this->file->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "Error opening file", this->file->errorString());
    }
    else
    {
        while(!this->file->atEnd())
             myStringList.append(this->file->readLine());
        this->file->close();
    }
    this->stringlist = myStringList;
    this->myxml = new MyXML(this->stringlist);
    Vector3f cam_pos = Vector3f(this->myxml->get_field("scene:view:cam_pos:x").toFloat(), this->myxml->get_field("scene:view:cam_pos:y").toFloat(), this->myxml->get_field("scene:view:cam_pos:z").toFloat());
    Vector3f look_at = Vector3f(this->myxml->get_field("scene:view:look_at:x").toFloat(), this->myxml->get_field("scene:view:look_at:y").toFloat(), this->myxml->get_field("scene:view:look_at:z").toFloat());
    Vector2 size = Vector2(this->myxml->get_field("scene:view:x_size").toInt(), this->myxml->get_field("scene:view:y_size").toInt());
    this->camera = new Camera(size, cam_pos, look_at, this->myxml->get_field("scene:view:fov").toFloat(), this->myxml->get_field("scene:view:alias").toFloat());
    this->objectCount = this->myxml->get_field("scene:object_list:count").toInt();
    this->objectList = new Object[this->objectCount];
    int i = 1;
    while (i < this->objectCount)
    {
        QString s = QString("scene:object_list:obj") + QString(QString::number(i) + QString(":type"));
        if (this->myxml->get_field(s.toLatin1().data()) == "sphere")
            this->objectList[i] = Sphere(Vector3f(QString("scene:object_list:obj") + QString::number(i) + QString(":center:"), this->myxml),  this->myxml->get_field("scene:object_list:radius").toFloat(), new Material(1, Color(0.0, 0.0, 1.0), 50, 0, Image("bite")));
        this->myxml->get_field(s.toLatin1().data());
        i++;
    }

}
