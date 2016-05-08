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

    Object *objectList[6];
    objectList[0] = new Sphere(Vector3f(-225, 100.0, 0.0), 100, new Material(1, Color(0.0, 0.0, 1.0), 50, 0, Image("bite")));
    objectList[1] = new Sphere(Vector3f(-112.0, -100.0, 0.0), 100, new Material(1, Color(1.0, 1.0, 0.0), 50, 0, Image("bite")));
    objectList[2] = new Sphere(Vector3f(0.0, 100.0, 0.0), 100, new Material(1, Color(0.25, 0.25, 0.25), 50, 0, Image("bite")));
    objectList[3] = new Sphere(Vector3f(112, -100.0, 0.0), 100, new Material(1, Color(0.0, 1.0, 0.0), 50, 0, Image("bite")));
    objectList[4] = new Sphere(Vector3f(225.0, 100.0, 0.0), 100, new Material(1, Color(1.0, 0.0, 0.0), 50, 0, Image("bite")));
    objectList[5] = new Plan(Vector3f(0.0, -.0, 0.0), Vector3f(0.0, -1.0, 0.0), new Material(1, Color(1.0, 0.0, 0.0), 50, 0, Image("bite")));

    for (pos.y = 0; pos.y < this->glWin->size().height(); pos.y++)
    {
        mutex->lock();
        for (pos.x = 0; pos.x < this->glWin->size().width(); pos.x++)
        {
            camera.processDir(pos);
            int   objTouched = -1;
            float hitDist = 20000.0;
            for (int obj_i = 0; obj_i < 6; obj_i++)
            {
                if (objectList[obj_i]->hit(camera, hitDist))
                    objTouched = obj_i;
            }
            if (objTouched != -1)
                break;

            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = objectList[objTouched]->material->color->r;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].g = objectList[objTouched]->material->color->g;
            this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].b = objectList[objTouched]->material->color->b;
             //Vector3f hitPoint = camera.start + camera.direction * hitDist;
             //
             ////normale on hit_pont, a faire avec des methodes pour chaque object
             //Vector3f normale = hitPoint - objectList[objTouched]->center;
             //float tmp = normale * normale;
             //if (tmp == 0.0f)
             //   break;
             //tmp = 1.0f / sqrtf(tmp);
             //normale = normale * tmp;

              /*material currentMat =
                      myScene.matTab[myScene.sphTab[currentSphere].material];

                  // calcul de la valeur d'éclairement au point
                  for (unsigned int j = 0; j < myScene.lgtTab.size(); ++j) {
                    light current = myScene.lgtTab[j];imageFile.put
                    vecteur dist = current.pos - newStart;
                    if (n * dist <= 0.0f)
                      continue;
                    float t = sqrtf(dist * dist);
                    if ( t <= 0.0f )
                      continue;
                    ray lightRay;
                    lightRay.start = newStart;
                    lightRay.dir = (1/t) * dist;
                    // calcul des ombres
                    bool inShadow = false;
                    for (unsigned int i = 0; i < myScene.sphTab.size(); ++i) {
                      if (hitSphere(lightRay, myScene.sphTab[i], t)) {
                        inShadow = true;
                        break;
                      }
                    }
                    if (!inShadow) {
                      // lambert
                      float lambert = (lightRay.dir * n) * coef;
                      red += lambert * current.red * currentMat.red;
                      green += lambert * current.green * currentMat.green;
                      blue += lambert * current.blue * currentMat.blue;
                    }
                  }

                  // on itére sur la prochaine reflexion
                  coef *= currentMat.reflection;
                  float reflet = 2.0f * (viewRay.dir * n);
                  viewRay.start = newStart;
                  viewRay.dir = viewRay.dir - reflet * n;

                  level++;
                }
                while ((coef > 0.0f) && (level < 10));
            {
                this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].r = objectList[objTouched]->material->color->r;
                this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].g = objectList[objTouched]->material->color->g;
                this->glWin->pixel[pos.x + pos.y * this->glWin->size().width()].b = objectList[objTouched]->material->color->b;
            }*/
        }
        mutex->unlock();
        this->glWin->update();
    }
}
