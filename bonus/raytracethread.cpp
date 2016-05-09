#include "raytracethread.h"

#include <QDebug>
#include <vector>

RaytraceThread::RaytraceThread(QMutex* mu, GlWindow *glWin)
{
    this->mutex= mu;
    this->glWin = glWin;
}

void RaytraceThread::run()
{
    Vector2 pos = Vector2(-1, -1);
    Camera  camera = Camera(global_scene->camera->win_size,
                            global_scene->camera->start,
                            global_scene->camera->look_at,
                            global_scene->camera->fov.x,
                            global_scene->camera->alliasing);
    while (++pos.y < this->glWin->size().height())
    {
        pos.x = -1;
        mutex->lock();
        while (++pos.x < this->glWin->size().width())
        {
            camera.processDir(pos);
            Color outColor = raytrace(camera.start, camera.direction, 0);
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = outColor.r;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].g = outColor.g;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].b = outColor.b;
        }
        mutex->unlock();
        this->glWin->update();
    }
}

Color RaytraceThread::raytrace(const Vector3f<float> &camStart, const Vector3f<float> &camDir, int depth)
{
    Camera camera;
    camera.start = camStart;
    camera.direction = camDir;
    Color outColor = Color();
    float tnear = INFINITY;
    int   objTouchedID = -1;
    for (int obj_i = 0; obj_i < global_scene->objectList.size(); obj_i++)
    {
        if (global_scene->objectList.at(obj_i)->hit(camera, tnear))
            objTouchedID = obj_i;
    }
    if (objTouchedID == -1)
        return (outColor);
    Object   *objTouched = global_scene->objectList.at(objTouchedID);
    Material *matTouched = objTouched->material;

    Vector3f<float> hitPoint = camera.start + camera.direction * tnear;
    Vector3f<float> hitNormale = objTouched->getNormale(camera, hitPoint);
    hitNormale.normalize();

    // If the normal and the view direction are not opposite to each other
    // reverse the normal direction. That also means we are inside the sphere so set
    // the inside bool to true. Finally reverse the sign of IdotN which we want
    // positive.

    float bias = 1e-4;
    bool  inside = false;
    if (camera.direction.dot(hitNormale) > 0)
    {
        hitNormale = -hitNormale;
        inside = true;
    }

    if ((matTouched->transparency > 0 || matTouched->reflect > 0) && depth < MAX_DEPTH)
    {
        float facingRate = -camera.direction.dot(hitNormale);

        // change the mix value to tweak the effect
        float fresnelEffect = mix(pow(1 - facingRate, 3), 1, 0.1);

        Vector3f<float> reflectDir = camera.direction - hitNormale * 2 * camera.direction.dot(hitNormale);
        reflectDir.normalize();
        Color reflectionColor = raytrace(hitPoint + hitNormale * bias, reflectDir, depth + 1);
        Color refractionColor;
        if (matTouched->transparency)
        {
            float ior = 1.1;
            float eta = (inside) ? ior : 1 / ior;
            float cosi = -hitNormale.dot(camera.direction);
            float k = 1 - eta * eta * (1 - cosi * cosi);
            Vector3f<float> refractDir = camera.direction * eta + hitNormale * (eta *  cosi - sqrt(k));
            refractDir.normalize();
            refractionColor = raytrace(hitPoint - hitNormale * bias, refractDir, depth + 1);
        }
        surfaceColor = (reflectionColor * fresneleffect + refractionColor * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
    }
    //else {
    //    // it's a diffuse object, no need to raytrace any further
    //    for (unsigned i = 0; i < spheres.size(); ++i) {
    //        if (spheres[i].emissionColor.x > 0) {
    //            // this is a light
    //            Vec3f transmission = 1;
    //            Vec3f lightDirection = spheres[i].center - hitPoint;
    //            lightDirection.normalize();
    //            for (unsigned j = 0; j < spheres.size(); ++j) {
    //                if (i != j) {
    //                    float t0, t1;
    //                    if (spheres[j].intersect(hitPoint + hitNormale * bias, lightDirection, t0, t1)) {
    //                        transmission = 0;
    //                        break;
    //                    }
    //                }
    //            }
    //            surfaceColor += sphere->surfaceColor * transmission *
    //            std::max(float(0), hitNormale.dot(lightDirection)) * spheres[i].emissionColor;
    //        }
    //    }
    //}
    //return surfaceColor + sphere->emissionColor;
}

float RaytraceThread::mix(const float &a, const float &b, const float &mix)
{
    return b * mix + a * (1 - mix);
}
