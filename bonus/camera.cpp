#include "camera.h"

Camera::Camera(const Vector2 size, const Vector3f start, const Vector3f look_at, const float fov, const int alliasing)
{
    this->win_size.x = size.x;
    this->win_size.y = size.y;

    this->start.x = start.x;
    this->start.y = start.y;
    this->start.z = start.z;

    this->look_at.x = look_at.x;
    this->look_at.y = look_at.y;
    this->look_at.z = look_at.z;

    /* configure fov */
    this->fov.x = fov;
    this->fov.y = this->fov.x * ((this->win_size.x / this->win_size.y) / 1.5);
    /* configure dir */

    this->alliasing = alliasing;
}
