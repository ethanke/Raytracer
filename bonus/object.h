#ifndef OBJECT_H
#define OBJECT_H

#include "vector3f.h"
#include "material.h"
#include "camera.h"

class Object
{
    public:
        Object();

        Vector3f    center;
        Material    *material;

        virtual bool hit(const Camera ray, float &old_dist);
        virtual QString getObjectType();

};

#else
    class Object;

#endif // OBJECT_H
