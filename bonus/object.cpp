#include "object.h"

#include "sphere.h"

Object::Object()
{

}

bool Object::hit(const Camera ray, float &old_dist)
{
    qDebug("unknown object\n");
    return (0);
}

QString Object::getObjectType()
{
    return (QString("unknow"));
}
