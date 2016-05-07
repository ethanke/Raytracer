#ifndef CAMERA_H
#define CAMERA_H

#include "vector2.h"
#include "vector2f.h"
#include "vector3f.h"

class Camera
{   
    public:
        Camera(const Vector2 size, const Vector3f start, const Vector3f look_at, const float fov, const int alliasing);

        Vector2     win_size;
        Vector3f    start;
        Vector3f    look_at;
        Vector3f    direction;
        Vector2f    fov;
        int         alliasing;
};

#endif // CAMERA_H
