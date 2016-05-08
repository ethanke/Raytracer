#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "object.h"
#include "camera.h"
#include "myxml.h"

class Scene
{
    public:
        Object *objectList;
        int objectCount;
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
