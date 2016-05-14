#include "raytracethread.h"

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
            Vector3f<float> outColor = raytrace(camera.start, camera.direction, 0, 1.0) * 255.0;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = outColor.x;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].g = outColor.y;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].b = outColor.z;
        }
        mutex->unlock();
        this->glWin->update();
    }
    qDebug("Raytracing finished");
}

Vector3f<float> RaytraceThread::raytrace(const Vector3f<float> &camStart, const Vector3f<float> &camDir, int depth, float coef)
{
    Camera          camera;
    camera.start =  camStart;
    camera.direction = camDir;
    Vector3f<float> outColor;
    float           Distance = INFINITY;
    int             obj_touched_id = -1;
    for(unsigned int obj_i = 0; obj_i < global_scene->objectList.size(); obj_i++)
    {
        if(global_scene->objectList.at(obj_i)->hit(camera, Distance))
            obj_touched_id = obj_i;
    }
    if (obj_touched_id == -1)
        return (outColor);
    Object *obj_touched = global_scene->objectList.at(obj_touched_id);
    Vector3f<float> hitPoint = camera.start + camera.direction * Distance;
    Vector3f<float> Normal = obj_touched->getNormale(camera, hitPoint);
    outColor = obj_touched->getObjectColor(hitPoint);

    if (obj_touched->material->sky > 0)
        return (outColor);

    if(obj_touched->material->reflect > 0.0f && depth < MAX_DEPTH && coef > 0.0)
    {
        Vector3f<float> ReflectedRay = reflect(camera.direction, Normal);
        outColor = mix(outColor, raytrace(hitPoint - camera.direction, ReflectedRay, depth + 1, coef * obj_touched->material->reflect), obj_touched->material->reflect * coef);
    }

    if (obj_touched->material->transparency > 0.0f && depth < MAX_DEPTH && coef > 0 &&
        obj_touched->getObjectType() == QString("sphere"))
    {
        Sphere *sphere = static_cast<Sphere *>(obj_touched);
        Vector3f<float> RefractedRay = refract(camera.direction, Normal, obj_touched->material->eior);
        Vector3f<float> L = sphere->center - hitPoint;
        float LdotRR = L.dot(RefractedRay);
        float D2 = L.length2() - LdotRR * LdotRR;
        float dist_to_refract = LdotRR + sqrt(sphere->radius * sphere->radius - D2);
        Vector3f<float> NewPoint = RefractedRay * dist_to_refract + hitPoint;
        Vector3f<float> NewNormal = (sphere->center - NewPoint) / sphere->radius;
        RefractedRay = refract(RefractedRay, NewNormal, obj_touched->material->ior);
        outColor = mix(outColor, raytrace(NewPoint, RefractedRay, depth + 1, coef), obj_touched->material->transparency);
    }

    return (outColor);
}

bool RaytraceThread::Shadow(Vector3f<float> &Point, Vector3f<float> &LightDirection, float LightDistance)
{
    Camera          camera;
    camera.start =  Point;
    camera.direction = LightDirection;

    for(unsigned int obj_i = 0; obj_i < global_scene->objectList.size(); obj_i++)
    {
        if(global_scene->objectList.at(obj_i)->hit(camera, LightDistance))
            return true;
    }
    return false;
}

Vector3f<float> RaytraceThread::reflect(const Vector3f<float> &i, const Vector3f<float> &n)
{
    return i - n * 2.0 * n.dot(i);
}

Vector3f<float> RaytraceThread::refract(const Vector3f<float> &i, const Vector3f<float> &n, float eta)
{
    Vector3f<float> r;

    float ndoti = n.dot(i);
    float k = 1.0 - eta * eta * (1.0 - ndoti * ndoti);
    if(k >= 0.0)
        r = i * eta - n * (eta * ndoti + sqrt(k));
    return r;
}

float RaytraceThread::clamp(const float &lo, const float &hi, const float &v)
{
    return std::max(lo, std::min(hi, v));
}

Vector3f<float> RaytraceThread::mix(const Vector3f<float> &u, const Vector3f<float> &v, float a)
{
    return u * (1.0f - a) + v * a;
}
