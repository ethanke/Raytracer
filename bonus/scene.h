#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "camera.h"
#include "myxml.h"

class Scene
{

public:
    Scene(QWidget *parent);
    QString path_file;
    QFile *file;
    QStringList stringlist;
    Camera *camera;
    MyXML *myxml;
};

#endif // SCENE_H
