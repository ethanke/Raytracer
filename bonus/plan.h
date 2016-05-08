#ifndef PLAN_H
#define PLAN_H

#include "object.h"
#include "vector3f.h"
#include "camera.h"

class Plan : public Object
{
    public:
        Plan();
        Plan(const Vector3f center, const Vector3f dir , Material *mat);
        Vector3f    center;
        Vector3f    direction;

        bool hit(const Camera ray, float &old_dist);
};

#endif // PLAN_H
