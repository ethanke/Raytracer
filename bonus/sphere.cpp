#include "sphere.h"

Sphere::Sphere()
{
    this->center = Vector3f<float>();
    this->radius = 100;
    this->material = new Material();

}

Sphere::Sphere(const Vector3f<float> center, const float radius, Material *mat)
{
    this->center.x = center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->radius = radius;
    this->material = mat;
}

bool Sphere::hit(const Camera ray, float &old_dist)
{
    Vector3f<float> dist  = this->center - ray.start;
    float           B     = dist.dot(ray.direction);
    float           delta = B * B - dist.length2() + this->radius * this->radius;
    if (delta < 0)
        return (0);
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

Vector3f<float> Sphere::getNormale(const Camera ray, const Vector3f<float> hitPoint)
{
  return (hitPoint - this->center);
}

QString Sphere::getObjectType()
{
    return (QString("sphere"));
}
