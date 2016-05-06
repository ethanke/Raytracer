#include "vector3f.h"

Vector3f::Vector3f()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}


Vector3f::Vector3f(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
