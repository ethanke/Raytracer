#include "raytracethread.h"

#include <QDebug>

RaytraceThread::RaytraceThread(QMutex* mu, GlWindow *glWin)
{
    this->mutex= mu;
    this->glWin = glWin;
}

void RaytraceThread::run()
{
    Vector2 pos;
    Camera  camera = Camera(global_scene->camera->win_size,
                            global_scene->camera->start,
                            global_scene->camera->look_at,
                            global_scene->camera->fov.x,
                            global_scene->camera->alliasing);

    Sphere tmp_spere = Sphere(Vector3f(), 100, Material());

    for (pos.y = 0; pos.y < this->glWin->size().height(); pos.y++)
    {
        mutex->lock();
        for (pos.x = 0; pos.x < this->glWin->size().width(); pos.x++)
        {
            camera.processDir(pos);
            float max_dist = 20000.0;
            if (tmp_spere.hit(camera, max_dist) == 1)
                this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = 1;
        }
        mutex->unlock();
        this->glWin->update();
    }
}
