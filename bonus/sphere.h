#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "vector3f.h"
#include "material.h"

class Sphere : public Object
{
    public:
        Sphere(const Vector3f center, const float radius, const Material mat);

        float       radius;
};

#endif // SPHERE_H
