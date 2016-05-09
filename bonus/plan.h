#ifndef PLAN_H
#define PLAN_H

#include "object.h"
#include "vector3f.hpp"
#include "camera.h"

class Plan : public Object
{
    public:
        Plan();
        Plan(const Vector3f<float> center, const Vector3f<float> dir , Material *mat);
        Vector3f<float> center;
        Vector3f<float> direction;

        virtual bool            hit(const Camera ray, float &old_dist);
        virtual Vector3f<float> getNormale(const Camera ray, const Vector3f<float> hitPoint);
        virtual QString         getObjectType();
};

#endif // PLAN_H
