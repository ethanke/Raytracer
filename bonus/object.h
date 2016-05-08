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

        bool hit(const Camera ray, float &old_dist);
};

#else
    class Object;
#endif // OBJECT_H
