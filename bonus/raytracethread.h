#ifndef RAYTRACETHREAD_H
#define RAYTRACETHREAD_H

#include <QThread>
#include <QMutex>
#include "vector2.h"
#include "color.h"
#include "glwindow.h"
#include "scene.h"
#include "global.h"
#include "sphere.h"

class RaytraceThread : public QThread
{
    private:
        QMutex      *mutex;
        GlWindow    *glWin;
        Scene       *scene;

    public:
        RaytraceThread(QMutex* mu, GlWindow *glWin);

    protected:
        void run();
};

#else

class RaytraceThread;

#endif // RAYTRACETHREAD_H
