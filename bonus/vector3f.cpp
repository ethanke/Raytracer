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

Vector3f Vector3f::operator * (float c)
{
   Vector3f out = {this->x *c, this->y * c, this->z * c };
   return (out);
}

Vector3f Vector3f::operator - (const Vector3f v1)
{
    Vector3f out = {v1.x - this->x, v1.y - this->y, v1.z - this->z };
    return (out);
}

float Vector3f::operator * (const Vector3f v1)
{
    return (v1.x * this->x + v1.y * this->y + v1.z * this->z);
}
