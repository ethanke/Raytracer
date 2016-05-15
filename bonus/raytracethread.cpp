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
    if (obj_touched->material->bump != 0.0)
        applyPerlin(hitPoint, Normal, obj_touched->material->bump);
    outColor = obj_touched->getObjectColor(hitPoint);

    if (obj_touched->material->id == 4 || obj_touched->material->id == 1)
    {
        /*  BOULE RAYE MDR */  /* marbre raté 1 */
        //float noiseCoef = 0.0;
        //for (int level = 1; level < 10; level ++)
        //{
        //    noiseCoef +=  (1.0f / level) * fabsf(float(noise(   level * 0.05 * hitPoint.x * 100 /*RADIUS*/,
        //                                                        level * 0.05 * hitPoint.y * 100 /*RADIUS*/,
        //                                                        level * 0.05 * hitPoint.z * 100 /*RADIUS*/)));
        //}
        //noiseCoef = 0.5 * sinf((hitPoint.x + hitPoint.y) * 0.05 + noiseCoef) + 0.5;
        //outColor = (outColor + ((Vector3f<float>( 10, 10, 10) / 25000.0) * noiseCoef + (Vector3f<float>( 200, 200, 200) / 25000.0) * (1.0 - noiseCoef))) / 2.0;

        /*  BOULE RAYE MDR */  /* marbre raté 2 */
        //double x = hitPoint.x * /*scale*/ 1;
        //double y = hitPoint.y * /*scale*/ 1;
        //double z = hitPoint.z * /*scale*/ 1;
        //double noiseCoef = 0;
        //
        //for (int level = 1; level < 10; level ++) {
        //   noiseCoef +=  (1.0f / level) * fabsf(noise(
        //      level * 0.05 * x,
        //      level * 0.15 * y,
        //      level * 0.05 * z
        //   ));
        //}
        //noiseCoef = 0.5f * sinf((x + y) * 0.05f + noiseCoef) + 0.5f;
        //outColor = (outColor + ((Vector3f<float>( 10, 10, 10) / 25000.0) * noiseCoef + (Vector3f<float>( 200, 200, 200) / 25000.0) * (1.0 - noiseCoef))) / 2.0;


        /*  TURBULENCE  */
        //double x = hitPoint.x * /*sclae*/ 0.25;
        //double y = hitPoint.y * /*sclae*/ 0.25;
        //double z = hitPoint.z * /*sclae*/ 0.25;
        //double noiseCoef = 0;
        //
        //for (int level = 1; level < 10; level ++) {
        //   noiseCoef += (1.0f / level) * fabsf(noise(
        //      level * 0.05 * x,
        //      level * 0.05 * y,
        //      level * 0.05 * z
        //   ));
        //}
        //outColor = (outColor + ((Vector3f<float>( 10, 10, 10) / 25000.0) * noiseCoef + (Vector3f<float>( 200, 200, 200) / 25000.0) * (1.0 - noiseCoef))) / 2.0;

        /*  WOODEN TEST 1 */
        //double x = hitPoint.x * /*scale*/ 0.0075;
        //double y = hitPoint.y * /*scale*/ 0.0075;
        //double z = hitPoint.z * /*scale*/ 0.0075;
        //double grain = noise(x, y, z) * 20;
        //grain = grain - (int)grain;
        //outColor = (outColor + ((Vector3f<float>(94, 65, 19) / 50000.0) * grain + (Vector3f<float>(125, 78, 2) / 50000.0) * (1.0 - grain))) / 2.0;

        /*  LOL GAY PRIDE MDR */
        //double x = hitPoint.x * /*scale*/ 1 * 0.5;
        //double y = hitPoint.y * /*scale*/ 1 * 0.5;
        //double z = hitPoint.z * /*scale*/ 1 * 0.5;
        //double noiseCoefA = 0;
        //double noiseCoefB = 0;
        //double noiseCoefC = 0;
        //
        //for (int level = 1; level < 10; level++) {
        //   noiseCoefA += (1.0f / level) * fabsf(noise(
        //      level * 0.35 * x,
        //      level * 0.05 * y,
        //      level * z
        //   ));
        //
        //   noiseCoefB += (1.0f / level) * fabsf(noise(
        //      level * x,
        //      level * 0.35 * y,
        //      level * 0.05 * z
        //   ));
        //
        //   noiseCoefC += (1.0f / level) * fabsf(noise(
        //      level * 0.05 * x,
        //      level * y,
        //      level * 0.35 * z
        //   ));
        //}
        //noiseCoefA = 0.5f * sinf((x + z) * 0.05f + noiseCoefA) + 0.5f;
        //noiseCoefB = 0.5f * sinf((y + x) * 0.05f + noiseCoefB) + 0.5f;
        //noiseCoefC = 0.5f * sinf((z + y) * 0.05f + noiseCoefC) + 0.5f;
        //outColor.x = (outColor.x + (0 / 25000.0) * noiseCoefA + (255 / 25000.0) * (1.0 - noiseCoefA)) / 2.0;
        //outColor.y = (outColor.y + (0 / 25000.0) * noiseCoefB + (255 / 25000.0) * (1.0 - noiseCoefB)) / 2.0;
        //outColor.z = (outColor.z + (0 / 25000.0) * noiseCoefC + (255 / 25000.0) * (1.0 - noiseCoefC)) / 2.0;
    }


    if (obj_touched->material->sky > 0)
        return (outColor);

    /* lightning */
        IlluminatePoint(obj_touched, hitPoint, Normal, outColor, camera);
    /* lightning */

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


#define AmbientOcclusion                        1
#define SoftShadows                             true
#define GISamples                               16
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
            return (Vector3f<float>(200.0) * ((1.0 * AO + 1.0 * NdotLD) / Attenuation));
    }

  return Vector3f<float>(200.0) * (1 * AO / Attenuation);
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

float RaytraceThread::clamp(const float &lo, const float &hi, const float &v)
{
    return std::max(lo, std::min(hi, v));
}

Vector3f<float> RaytraceThread::mix(const Vector3f<float> &u, const Vector3f<float> &v, float a)
{
    return u * (1.0f - a) + v * a;
}
