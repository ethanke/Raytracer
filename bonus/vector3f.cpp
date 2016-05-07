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
    Vector3f out = {this->x - v1.x, this->y - v1.y, this->z - v1.z};
    return (out);
}

float Vector3f::operator * (const Vector3f v1)
{
    return (v1.x * this->x + v1.y * this->y + v1.z * this->z);
}

Vector3f Vector3f::normalize()
{
  Vector3f  out;

  out.x = this->x / sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
  out.y = this->y / sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
  out.z = this->z / sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
  this->x = out.x;
  this->y = out.y;
  this->z = out.z;
  return (out);
}
