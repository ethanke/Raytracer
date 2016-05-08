#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "vector3f.h"
#include "material.h"
#include "camera.h"

class Sphere : public Object
{
    public:
        Sphere();
        Sphere(const Vector3f center, const float radius, Material *mat);
        float       radius;

        bool hit(const Camera ray, float &old_dist);
};

#endif // SPHERE_H
