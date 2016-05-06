#ifndef CAMERA_H
#define CAMERA_H

#include "vector2f.h"
#include "vector3f.h"

class Camera
{   
    public:
        Camera(const Vector3f start, const Vector3f look_at, const Vector2f fov, const int alliasing);

        Vector3f    start;
        Vector3f    look_at;
        Vector3f    direction;
        Vector2f    fov;
        int         alliasing;
};

#endif // CAMERA_H
