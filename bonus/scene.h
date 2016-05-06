#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

class Scene
{

public:
    Scene(QWidget *parent);
    QString path_file;
    QFile *file;
    QStringList stringlist;
};

#endif // SCENE_H
