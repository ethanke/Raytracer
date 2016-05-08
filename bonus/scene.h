#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>

#include "object.h"
#include "camera.h"
#include "light.h"
#include "myxml.h"

class Scene
{
    public:
        std::vector<Object *> objectList;
        std::vector<Light  *> lightList;
        int objectCount;
        int lightCount;
        Scene(QWidget *parent);
        QString path_file;
        QFile *file;
        QStringList stringlist;
        Camera *camera;
        MyXML *myxml;
};

#else
    class Scene;

#endif // SCENE_H
