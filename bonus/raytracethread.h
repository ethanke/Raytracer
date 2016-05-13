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
        Vector3f<float> raytrace(const Vector3f<float> &camStart, const Vector3f<float> &camDir, int depth);
        void  IlluminatePoint(Object *Object, Vector3f<float> &Point, Vector3f<float> &Normal, Vector3f<float> &Color, Camera &camera);
        float AmbientOcclusionFactor(Object *object, Vector3f<float> &Point, Vector3f<float> &Normal);
        Vector3f<float> LightIntensity(Object *Object, Vector3f<float> &Point, Vector3f<float> &Normal, Vector3f<float> &LightPosition, Light *light, float AO);
        bool Shadow(Vector3f<float> &Point, Vector3f<float> &LightDirection, float LightDistance);
        Vector3f<float> reflect(const Vector3f<float> &i, const Vector3f<float> &n);
        Vector3f<float> refract(const Vector3f<float> &i, const Vector3f<float> &n, float eta);
        Vector3f<float> mix(const Vector3f<float> &u, const Vector3f<float> &v, float a);

    public:
        RaytraceThread(QMutex* mu, GlWindow *glWin);

    protected:
        void run();

};

#else

class RaytraceThread;

#endif // RAYTRACETHREAD_H
