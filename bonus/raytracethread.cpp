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

    Sphere *objectList = new Sphere[5];
    objectList[0] = Sphere(Vector3f(-225, 100.0, 0.0), 100, new Material(1, Color(0.0, 0.0, 1.0), 50, 0, Image("bite")));
    objectList[1] = Sphere(Vector3f(-112.0, -100.0, 0.0), 100, new Material(1, Color(0.0, 1.0, 1.0), 50, 0, Image("bite")));
    objectList[2] = Sphere(Vector3f(0.0, 100.0, 0.0), 100, new Material(1, Color(0.25, 0.25, 0.25), 50, 0, Image("bite")));
    objectList[3] = Sphere(Vector3f(112, -100.0, 0.0), 100, new Material(1, Color(0.0, 1.0, 0.0), 50, 0, Image("bite")));
    objectList[4] = Sphere(Vector3f(225.0, 100.0, 0.0), 100, new Material(1, Color(1.0, 0.0, 0.0), 50, 0, Image("bite")));

    for (pos.y = 0; pos.y < this->glWin->size().height(); pos.y++)
    {
        mutex->lock();
        for (pos.x = 0; pos.x < this->glWin->size().width(); pos.x++)
        {
            camera.processDir(pos);
            int   objTouched = -1;
            float max_dist = 20000.0;
            for (int obj_i = 0; obj_i < 5; obj_i++)
            {
                if (objectList[obj_i].hit(camera, max_dist))
                    objTouched = obj_i;
            }
            if (objTouched != -1)
            {
                this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = objectList[objTouched].material->color->r;
                this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].g = objectList[objTouched].material->color->g;
                this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].b = objectList[objTouched].material->color->b;
            }
        }
        mutex->unlock();
        this->glWin->update();
    }
}
