#include "plan.h"

Plan::Plan()
{
    this->center = Vector3f();
    this->direction = Vector3f(0.0, 1.0, 0.0);
    this->material = new Material();

}

Plan::Plan(const Vector3f center, const Vector3f dir , Material *mat)
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
    float denom = this->direction * ray.direction;
    if (denom > 0)
    {
        Vector3f p0l0 = this->center - ray.start;
        float dist = (this->direction * p0l0) / denom;
        if (dist > 0.1 && old_dist > dist)
        {
            old_dist = dist;
            return (1);
        }
    }
    return (0);
}

QString Plan::getObjectType()
{
    return (QString("plan"));
}
