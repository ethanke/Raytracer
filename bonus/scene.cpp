#include "scene.h"

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
    qDebug() << this->camera->start.x;
    qDebug() << this->camera->start.y;
    qDebug() << this->camera->start.z;
}
