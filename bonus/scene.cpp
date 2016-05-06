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
}


