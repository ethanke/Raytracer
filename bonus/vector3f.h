#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <QString>
#include <math.h>
#include "myxml.h"

class Vector3f
{
    public:
        Vector3f();
        Vector3f(const float x, const float y, const float z);
        Vector3f(const QString beg_string, MyXML *file);

        float x;
        float y;
        float z;

        Vector3f operator * (const float c);
        Vector3f operator - (const Vector3f v1);
        Vector3f operator + (const Vector3f v1);
        float    operator * (const Vector3f v1);

        Vector3f normalize();

    private:

};

#endif // VECTOR3F_H
