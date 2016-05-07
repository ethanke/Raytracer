#include "sphere.h"

Sphere::Sphere(const Vector3f center, const float radius, const Material mat)
{
    this->center.x = center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->radius = radius;
    this->material = new Material();
}

bool Sphere::hit(const Camera ray, float *old_dist)
{
    Vector3f dist = this->center - ray.start;
    float B = dist * ray.direction;
    float D = B * B - dist * dist + this->radius * this->radius;
    if (D < 0.0f)
      return false;
    float t0 = B - sqrtf(D);
    float t1 = B + sqrtf(D);
    bool retvalue = false;
    if ((t0 > 0.1f) && (t0 < *old_dist))
    {
      *old_dist = t0;
      retvalue = true;
    }
    if ((t1 > 0.1f) && (t1 < *old_dist))
    {
      *old_dist = t1;
      retvalue = true;
    }
    return retvalue;
}
