#include "scene.h"
#include "sphere.h"
#include "cone.h"
#include "plan.h"
#include <qdebug.h>

Scene::Scene(QWidget *parent, int y)
{
    if (y == 0)
    {
    this->path_file = QFileDialog::getOpenFileName(parent, QObject::tr("Open File"),"/path/to/file/", QObject::tr("Files Xml's only (*.xml)"));
    this->file = new QFile(this->path_file);
    }
    else
        this->file = new QFile("/Users/ethankerdelhue/Documents/Shared/Raytracer/scene/olympiques_transpa.xml");
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
    Vector3f<float> cam_pos = Vector3f<float>(this->myxml->get_field("scene:view:cam_pos:x").toFloat(),
                                        this->myxml->get_field("scene:view:cam_pos:y").toFloat(),
                                        this->myxml->get_field("scene:view:cam_pos:z").toFloat());
    Vector3f<float> look_at = Vector3f<float>(this->myxml->get_field("scene:view:look_at:x").toFloat(),
                                        this->myxml->get_field("scene:view:look_at:y").toFloat(),
                                        this->myxml->get_field("scene:view:look_at:z").toFloat());
    Vector2 size = Vector2(this->myxml->get_field("scene:view:x_size").toInt(), this->myxml->get_field("scene:view:y_size").toInt());
    this->camera = new Camera(size, cam_pos, look_at, this->myxml->get_field("scene:view:fov").toFloat(), this->myxml->get_field("scene:view:alias").toFloat());
    int i = 1;
    this->matCount = this->myxml->get_field("scene:material_list:count").toInt();
    while (i <= this->matCount)
    {
        this->matList.push_back(new Material(QString("Mat_xml") + QString(i), i, Color(this->myxml->get_field((QString("scene:material_list:mat")
                                                                              + QString::number(i)
                                                                              + QString(":red")).toLatin1().data()).toFloat() / 255.0,
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":green")).toLatin1().data()).toFloat() / 255.0,
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":blue")).toLatin1().data()).toFloat() / 255.0),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":reflect")).toLatin1().data()).toFloat(),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":transparency")).toLatin1().data()).toFloat(),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":ior")).toLatin1().data()).toFloat(),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":bump")).toLatin1().data()).toFloat(),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":sky")).toLatin1().data()).toInt(),
                                                      this->myxml->get_field((QString("scene:material_list:mat") + QString::number(i) + QString(":texture")).toLatin1().data())));
        i++;
    }
    qDebug() << "materiaux loaded\n";

    this->objectCount = this->myxml->get_field("scene:object_list:count").toInt();
    i = 1;
    while (i <= this->objectCount)
    {
        if (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":type")).toLatin1().data()) == QString("sphere"))
        {
            Vector3f<float> sphere_center = Vector3f<float>(QString("scene:object_list:obj") + QString::number(i) + QString(":center:"), this->myxml);
            float           sphere_radius = this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":radius")).toLatin1().data()).toFloat();
            int             sphere_mat_id = (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":material_id")).toLatin1().data())).toInt() - 1;
            Sphere *sphere_tmp = new Sphere(sphere_center, sphere_radius, this->matList[sphere_mat_id]);
            this->objectList.push_back(sphere_tmp);
        }

        if (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":type")).toLatin1().data()) == QString("plan"))
        {
            Vector3f<float> plan_center  = Vector3f<float>(QString("scene:object_list:obj") + QString::number(i) + QString(":center:"), this->myxml);
            Vector3f<float> plan_dir     = Vector3f<float>(QString("scene:object_list:obj") + QString::number(i) + QString(":dir:"), this->myxml);
            int             plan_mat_id  = (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":material_id1")).toLatin1().data())).toInt() - 1;
            int             plan_mat_id2 = (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":material_id2")).toLatin1().data())).toInt() - 1;
            Plan *plan_tmp = new Plan(plan_center, plan_dir, this->matList[plan_mat_id], this->matList[plan_mat_id2]);
            this->objectList.push_back(plan_tmp);
        }

        if (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":type")).toLatin1().data()) == QString("cone"))
        {
            Vector3f<float> cone_center  = Vector3f<float>(QString("scene:object_list:obj") + QString::number(i) + QString(":center:"), this->myxml);
            Vector3f<float> cone_dir     = Vector3f<float>(QString("scene:object_list:obj") + QString::number(i) + QString(":dir:"), this->myxml);
            float           cone_radius = this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":radius")).toLatin1().data()).toFloat();
            float           cone_height = this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":height")).toLatin1().data()).toFloat();
            int             cone_mat_id  = (this->myxml->get_field((QString("scene:object_list:obj") + QString::number(i) + QString(":material_id")).toLatin1().data())).toInt() - 1;
            Cone *cone_tmp = new Cone(cone_center, cone_dir, cone_radius, cone_height, this->matList[cone_mat_id]);
            this->objectList.push_back(cone_tmp);
        }

        i++;
    }
    qDebug() << "object loaded\n";

    i = 1;
    this->lightCount = this->myxml->get_field("scene:light_list:count").toInt();
    while (i <= this->lightCount)
    {
        this->lightList.push_back(new Light(Vector3f<float>(QString("scene:light_list:light") + QString::number(i) + QString(":center:"), this->myxml),
                                            this->myxml->get_field((QString("scene:light_list:light") + QString::number(i) + ":intensity").toLatin1().data()).toFloat()));
        i++;
    }
}
