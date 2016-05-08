#include "light.h"

Light::Light(Vector3f center, float inten)
{
    this->center.x = center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->intensity = inten;
}
