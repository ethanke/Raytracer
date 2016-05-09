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
#include "plan.h"

#define     MAX_DEPTH       10

class RaytraceThread : public QThread
{
    private:
        QMutex      *mutex;
        GlWindow    *glWin;
        Scene       *scene;
        Color       raytrace(const Vector3f<float> &camStart, const Vector3f<float> &camDir, int depth);
        float       mix(const float &a, const float &b, const float &mix);

    public:
        RaytraceThread(QMutex* mu, GlWindow *glWin);

    protected:
        void run();

};

#else

class RaytraceThread;

#endif // RAYTRACETHREAD_H
