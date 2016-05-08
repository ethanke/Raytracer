#ifndef LIGHT_H
#define LIGHT_H

#include "vector3f.h"
#include "material.h"
#include "object.h"

class Light
{

public:
        Light(Vector3f center, float inten);

        Vector3f		center;
        float		intensity;

};

#endif // LIGHT_H
