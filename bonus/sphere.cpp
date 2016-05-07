#include "sphere.h"

Sphere::Sphere(const Vector3f center, const float radius, const Material mat)
{
    this->center.x = center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->radius = radius;
    this->material = new Material();
}

bool Sphere::hit(const Camera ray, float &old_dist)
{
    Vector3f    dist  = this->center - ray.start;
    float       B     = dist * ray.direction;
    float		delta = B * B - dist * dist + this->radius * this->radius;
    if (delta < 0)
        return (0);
    return (1);
    float       t0 = B - sqrt(delta);
    float       t1 = B + sqrt(delta);
    if (t0 < t1 && (t0 > 0.0) && (t0 < old_dist))
    {
        old_dist = t0;
        return (1);
    }
    else if ((t1 > 0.0) && (t1 < old_dist))
    {
        old_dist = t1;
        return (1);
    }
    return (0);
}
