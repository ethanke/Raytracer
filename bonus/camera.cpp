#include "camera.h"

Camera::Camera(const Vector3f start, const Vector3f look_at, const Vector2f fov, const int alliasing)
{
    this->start.x = start.x;
    this->start.y = start.y;
    this->start.z = start.z;

    this->look_at.x = look_at.x;
    this->look_at.y = look_at.y;
    this->look_at.z = look_at.z;

    /* configure fov */

    /* configure dir */

    this->alliasing = alliasing;
}
