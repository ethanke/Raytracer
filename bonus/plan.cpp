#include "plan.h"

Plan::Plan()
{
    this->center = Vector3f<float>();
    this->direction = Vector3f<float>(0.0, 1.0, 0.0);
    this->material = new Material();

}

Plan::Plan(const Vector3f<float> center, const Vector3f<float> dir , Material *mat)
{
    this->center.x = center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->direction.x = dir.x;
    this->direction.y = dir.y;
    this->direction.z = dir.z;
    this->material = mat;
}

bool Plan::hit(const Camera ray, float &old_dist)
{
    float denom = this->direction.dot(ray.direction);
    if (denom > 0)
    {
        Vector3f<float> p0l0 = this->center - ray.start;
        float dist = (p0l0.dot(this->direction)) / denom;
        if (dist > 0.1 && old_dist > dist)
        {
            old_dist = dist;
            return (1);
        }
    }
    return (0);
}

Vector3f<float> Plan::getNormale(const Camera ray, const Vector3f<float> hitPoint)
{
  return (this->direction);
}

QString Plan::getObjectType()
{
    return (QString("plan"));
}
