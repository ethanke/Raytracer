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
    Vector3f cam_pos = Vector3f(this->myxml->get_field("scene:view:cam_pos:x").toFloat(),
                                this->myxml->get_field("scene:view:cam_pos:y").toFloat(),
                                this->myxml->get_field("scene:view:cam_pos:z").toFloat());
    Vector3f look_at = Vector3f(this->myxml->get_field("scene:view:look_at:x").toFloat(),
                                this->myxml->get_field("scene:view:look_at:y").toFloat(),
                                this->myxml->get_field("scene:view:look_at:z").toFloat());
    Vector2 size = Vector2(this->myxml->get_field("scene:view:x_size").toInt(), this->myxml->get_field("scene:view:y_size").toInt());
    this->camera = new Camera(size, cam_pos, look_at, this->myxml->get_field("scene:view:fov").toFloat(), this->myxml->get_field("scene:view:alias").toFloat());
    int i = 1;
    this->matCount = this->myxml->get_field("scene:material_list:count").toInt();
    while (i <= this->matCount)
    {
        this->matList.push_back(new Material(i, Color(this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":red")).toLatin1().data()).toFloat() / 255.0,
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":green")).toLatin1().data()).toFloat() / 255.0,
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":blue")).toLatin1().data()).toFloat() / 255.0),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":reflect")).toLatin1().data()).toFloat(),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":bump")).toLatin1().data()).toFloat(),
                                                      new Image(this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":texture")).toLatin1().data()))));
        i++;
    }
    qDebug() << "materiaux loaded\n";

    this->objectCount = this->myxml->get_field("scene:object_list:count").toInt();
    i = 1;
    while (i <= this->objectCount)
    {
        if (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":type")).toLatin1().data()) == QString("sphere"))
        {
            Vector3f sphere_center = Vector3f(QString("scene:object_list:obj") + QString::number(i) + QString(":center:"), this->myxml);
            float    sphere_radius = this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":radius")).toLatin1().data()).toFloat();
            int      sphere_mat_id = (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":material_id")).toLatin1().data())).toInt() - 1;
            Sphere *sphere_tmp = new Sphere(sphere_center, sphere_radius, this->matList[sphere_mat_id]);
            this->objectList.push_back(sphere_tmp);
        }
        /*QString s = QString("scene:object_list:obj") + QString::number(i) + QString(":type");
        if (this->myxml->get_field(s.toLatin1().data()) == "sphere")
            this->objectList.push_back(new Sphere(Vector3f(QString("scene:object_list:obj") + QString::number(i) + QString(":center:"), this->myxml),
                                                  this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":radius")).toLatin1().data()).toFloat(),
                                                  global_scene->matList[((this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":material_id")).toLatin1().data())).toInt() - 1)]));*/
        i++;
    }
    qDebug() << "object loaded\n";

    i = 1;
    this->lightCount = this->myxml->get_field("scene:light_list:count").toInt();
    while (i <= this->lightCount)
    {
        this->lightList.push_back(new Light(Vector3f(QString("scene:light_list:light") + QString::number(i) + QString(":center:"), this->myxml),
                                            this->myxml->get_field((QString("scene:light_list:light") + QString::number(i) + ":intensity").toLatin1().data()).toFloat()));
        i++;
    }
}
