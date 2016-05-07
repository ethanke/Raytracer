#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "vector3f.h"
#include "material.h"
#include "camera.h"

class Sphere : public Object
{
    public:
        Sphere(const Vector3f center, const float radius, const Material mat);
        bool hit(const Camera ray, float &old_dist);

        float       radius;
};

#endif // SPHERE_H
