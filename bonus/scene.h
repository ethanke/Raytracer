#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <Qstring>
#include <QFile>
class Scene
{

public:
    Scene();
    QString path_file;
    QFile *file;
};

#endif // SCENE_H
