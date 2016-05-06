#include "sphere.h"

Sphere::Sphere(const Vector3f center, const float radius, const Material mat)
{
    this->center.x = center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->radius = radius;
    this->material = new Material(mat.id, mat.color, mat.reflect, mat.bump, mat.texture);
}
