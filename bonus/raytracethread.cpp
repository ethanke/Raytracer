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
    Vector2 pos;
    Camera  camera = Camera(global_scene->camera->win_size,
                            global_scene->camera->start,
                            global_scene->camera->look_at,
                            global_scene->camera->fov.x,
                            global_scene->camera->alliasing);
    for (pos.y = 0; pos.y < this->glWin->size().height(); pos.y++)
    {
        mutex->lock();
        for (pos.x = 0; pos.x < this->glWin->size().width(); pos.x++)
        {
            float coef = 1.0f;
            int   depth = 0;
            camera.processDir(pos);
            while ((coef > 0.0f) && (depth < 10))
            {
                int   objTouched = -1;
                float hitDist = 20000.0;
                for (int obj_i = 0; obj_i < global_scene->objectList.size(); obj_i++)
                {
                    if (global_scene->objectList.at(obj_i)->hit(camera, hitDist))
                        objTouched = obj_i;
                }
                if (objTouched != -1)
                {
                    this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = global_scene->objectList.at(objTouched)->material->color->r;
                    this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].g = global_scene->objectList.at(objTouched)->material->color->g;
                    this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].b = global_scene->objectList.at(objTouched)->material->color->b;

                    Vector3f hitPoint = camera.start + camera.direction * hitDist;

                    /*normale on hit_pont, a faire avec des methodes pour chaque object, ini fait pour une sphere*/
                    Vector3f normale = hitPoint - global_scene->objectList[objTouched]->center;
                    float tmp = normale * normale;
                    if (tmp == 0.0f)
                       break;
                    tmp = 1.0f / sqrtf(tmp);
                    normale = normale * tmp;

                    //// calcul de la valeur d'éclairement
                    //for (unsigned int j = 0; j < myScene.lgtTab.size(); ++j)
                    //{
                    //    light current = myScene.lgtTab[j];imageFile.put
                    //    vecteur dist = current.pos - newStart;
                    //    if (n * dist <= 0.0f)
                    //        continue;
                    //    float t = sqrtf(dist * dist);
                    //    if ( t <= 0.0f )
                    //        continue;
                    //    ray lightRay;
                    //    lightRay.start = newStart;
                    //    lightRay.dir = (1/t) * dist;
                    //    // calcul des ombres
                    //    bool inShadow = false;
                    //    for (unsigned int i = 0; i < myScene.sphTab.size(); ++i)
                    //    {
                    //        if (hitSphere(lightRay, myScene.sphTab[i], t))
                    //        {
                    //            inShadow = true;
                    //            break;
                    //        }
                    //    }
                    //    if (!inShadow)
                    //    {
                    //      // lambert
                    //      float lambert = (lightRay.dir * n) * coef;
                    //      red += lambert * current.red * currentMat.red;
                    //      green += lambert * current.green * currentMat.green;
                    //      blue += lambert * current.blue * currentMat.blue;
                    //    }
                    //}

                    // on itére sur la prochaine reflexion
                    //coef *= currentMat.reflection;
                    //float reflet = 2.0f * (viewRay.dir * n);
                    //viewRay.start = newStart;
                    //viewRay.dir = viewRay.dir - reflet * n;
                }
                depth++;
            }
        }
        mutex->unlock();
        this->glWin->update();
    }
}
