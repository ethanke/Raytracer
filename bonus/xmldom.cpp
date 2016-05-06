#include "xmldom.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

Xml_Dom::Xml_Dom() : QWidget()
{
    //The QDomDocument class represents an XML document.
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f("/Users/ethankerdelhue/Documents/Shared/Raytracer/scene/olympiques.xml");
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
         qDebug("Erreur : Chargement du fichier cancel");
        return;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();
    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();

    // Get root names and attributes
    QString Type=root.tagName();
    qDebug(Type.toStdString().c_str());
    QDomElement Component=root.firstChild().toElement();
    while(!Component.isNull())
    {

        qDebug(Component.tagName().toStdString().c_str());
        QDomElement Child=Component.firstChild().toElement();
        while (!Child.isNull())
                {

            qDebug(Component.tagName().toStdString().c_str());
                QDomElement Component=root.firstChild().toElement();
                Child = Child.nextSibling().toElement();
                }
    }
}

Xml_Dom::~Xml_Dom()
{

}
