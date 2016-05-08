#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "global.h"
#include "vector2.h"
#include "vector2f.h"
#include "vector3f.h"

class Camera
{   
    public:
        Camera(const Vector2 size, const Vector3f start, const Vector3f look_at, const float fov, const int alliasing);
        void update_fov(float change);

        Vector2     win_size;
        Vector3f    start;
        Vector3f    look_at;
        Vector3f    direction;
        Vector2f    cam_rot;
        Vector2f    fov;
        int         alliasing;

        void processDir(Vector2 pos);
};

#else
    class Camera;

#endif // CAMERA_H
