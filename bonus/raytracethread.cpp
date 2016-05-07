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
    qDebug() << global_scene->camera->start.x;
    for (pos.y = 0; pos.y < 720; pos.y++)
    {
        mutex->lock();
        for (pos.x = 0; pos.x < 1080; pos.x++)
        {

            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = 1;
        }
        mutex->unlock();
        this->glWin->update();
    }
}
