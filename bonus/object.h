#ifndef OBJECT_H
#define OBJECT_H

#include "vector3f.h"
#include "material.h"

class Object
{
    public:
        Object();

        Vector3f    center;
        Material    *material;
};

#endif // OBJECT_H
