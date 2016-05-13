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
            Vector3f<float> outColor = raytrace(camera.start, camera.direction, 0) * 255.0;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = outColor.x;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].g = outColor.y;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].b = outColor.z;
        }
        mutex->unlock();
        this->glWin->update();
    }
    qDebug("Raytracing finished");
}

#define IOR     1.5
#define EIOR    (1.0 / IOR)

Vector3f<float> RaytraceThread::raytrace(const Vector3f<float> &camStart, const Vector3f<float> &camDir, int depth)
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
    outColor = Vector3f<float>(obj_touched->material->color->r, obj_touched->material->color->g, obj_touched->material->color->b) / 255.0;
    Vector3f<float> hitPoint = camera.start + camera.direction * Distance;
    Vector3f<float> Normal = obj_touched->getNormale(camera, hitPoint);

    //if(Textures && Data.Sphere->Texture)
    //{
    //    float s = atan2(Normal.x, Normal.z) * M_1_PI_2 + 0.5f;
    //    float t = asin(Normal.y < -1.0f ? -1.0f : Normal.y > 1.0f ? 1.0f : Normal.y) * (float)M_1_PI + 0.5f;
    //
    //    outColor *= Data.Sphere->Texture->GetColorBilinear(s, t);
    //}

    if (obj_touched->material->sky != 0)
        return (outColor);
    IlluminatePoint(obj_touched, hitPoint, Normal, outColor, camera);

    if (obj_touched->material->transparency > 0.0f && obj_touched->getObjectType() == QString("sphere"))
    {
        Sphere *sphere = static_cast<Sphere *>(obj_touched);
        Vector3f<float> RefractedRay = refract(camera.direction, Normal, obj_touched->material->eior);
        Vector3f<float> L = sphere->center - hitPoint;
        float LdotRR = L.dot(RefractedRay);
        float D2 = L.length2() - LdotRR * LdotRR;
        float dist_to_refract = LdotRR + sqrt(sphere->radius * sphere->radius - D2);
        Vector3f<float> NewPoint = RefractedRay * dist_to_refract + hitPoint;
        Vector3f<float> NewNormal = (sphere->center - NewPoint) * sphere->radius;
        RefractedRay = refract(RefractedRay, NewNormal, obj_touched->material->ior);
        Camera refractCam;
        refractCam.start = NewPoint;
        refractCam.direction = RefractedRay;
        outColor = mix(outColor, raytrace(NewPoint, RefractedRay, depth + 1), obj_touched->material->transparency);
    }

    //if(obj_touched->material->reflect > 0.0f)
    //{
    //    Vector3f<float> ReflectedRay = reflect(camera.direction, Normal);
    //    outColor = mix(outColor, raytrace(hitPoint, ReflectedRay, depth + 1), (float)obj_touched->material->reflect);
    //}

    return (outColor);
}

#define AmbientOcclusion                        1
#define SoftShadows                             true
#define GISamples                               256
#define TDRM                                    (2.0 / (float)RAND_MAX)
#define ODGISamples                             (1.0f / (float)GISamples)
#define AmbientOcclusionIntensity               1
#define ODGISamplesMAmbientOcclusionIntensity   (ODGISamples * AmbientOcclusionIntensity)

void RaytraceThread::IlluminatePoint(Object *Object, Vector3f<float> &Point, Vector3f<float> &Normal, Vector3f<float> &Color, Camera &camera)
{
    float AO = 1.0f;

   if(AmbientOcclusion)
     AO = AmbientOcclusionFactor(Object, Point, Normal);

    if(global_scene->lightList.size() == 0)
    {
        float NdotCD = Normal.dot((camera.start - Point).normalize());
        if(NdotCD > 0.0f)
            Color *= (0.5 * (AO + NdotCD)) / 50;
        else
            Color *= (0.5 * AO) / 50;
    }
    if(SoftShadows == false)
    {
        Vector3f<float> LightsIntensitiesSum;

        for(unsigned int light_i = 0; light_i < global_scene->lightList.size(); light_i++)
            LightsIntensitiesSum += LightIntensity(Object, Point, Normal, global_scene->lightList.at(light_i)->center, global_scene->lightList.at(light_i), AO);

        Color *= LightsIntensitiesSum;
    }
    else
    {
        Vector3f<float> LightsIntensitiesSum;

        for(unsigned int light_i = 0; light_i < global_scene->lightList.size(); light_i++)
        {
            for(int i = 0; i < GISamples; i++)
            {
                Vector3f<float> RandomRay = Vector3f<float>(TDRM * (float)rand() - 1.0, TDRM * (float)rand() - 1.0, TDRM * (float)rand() - 1.0);
                Vector3f<float> RandomLightPosition = RandomRay * 50.0 + global_scene->lightList.at(light_i)->center;
                LightsIntensitiesSum += LightIntensity(Object, Point, Normal, RandomLightPosition, global_scene->lightList.at(light_i), AO);
            }
        }
        Color *= LightsIntensitiesSum * ODGISamples;
    }
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


Vector3f<float> RaytraceThread::LightIntensity(Object *Object, Vector3f<float> &Point, Vector3f<float> &Normal, Vector3f<float> &LightPosition, Light *light, float AO)
{
    Vector3f<float> LightDirection = LightPosition - Point;

    float LightDistance2 = LightDirection.length2();
    float LightDistance = sqrt(LightDistance2);
    LightDirection *= 1.0f / LightDistance;
    float Attenuation = 0.125 * LightDistance2 + 0.100 * LightDistance + 1.0;
    float NdotLD = Normal.dot(LightDirection);
    if(NdotLD > 0.0f)
    {
        if(Shadow(Point, LightDirection, LightDistance) == false)
            return (Vector3f<float>(175.0) * ((1.0 * AO + 1.0 * NdotLD) / Attenuation));
    }

  return Vector3f<float>(175.0) * (1 * AO / Attenuation);
}

float RaytraceThread::AmbientOcclusionFactor(Object *object, Vector3f<float> &Point, Vector3f<float> &Normal)
{
  float AO = 0.0f;

  for (int i = 0; i < GISamples; i++)
  {
      Vector3f<float> RandomRay = (Vector3f<float>(TDRM * (float)rand() - 1.0f, TDRM * (float)rand() - 1.0f, TDRM * (float)rand() - 1.0f)).normalize();
      float NdotRR = Normal.dot(RandomRay);
      if (NdotRR < 0.0f)
        {
          RandomRay = -RandomRay;
          NdotRR = -NdotRR;
        }
      Camera camera;
      camera.start = Point;
      camera.direction = RandomRay;
      float Distance = INFINITY;
      for (unsigned int obj_i = 0; obj_i < global_scene->objectList.size(); obj_i++)
          global_scene->objectList.at(obj_i)->hit(camera, Distance);
      AO += NdotRR / (1.0f + Distance * Distance);
  }

  return 1.0f - AO * ODGISamplesMAmbientOcclusionIntensity;
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


Vector3f<float> RaytraceThread::mix(const Vector3f<float> &u, const Vector3f<float> &v, float a)
{
    return u * (1.0f - a) + v * a;
}
