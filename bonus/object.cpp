#include "object.h"

Object::Object()
{

}

bool Object::hit(const Camera ray, float &old_dist)
{
    return (this->hit(ray, old_dist));
}
