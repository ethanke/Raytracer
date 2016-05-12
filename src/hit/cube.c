/*
** cone.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri Apr 29 05:28:00 2016 Victor Sousa
** Last update Thu May 12 11:03:44 2016 Philippe Lefevre
*/

#include		"main.h"

int			hit_cube(t_ray *r, t_cube *c, float *t)
{
  (void)r;
  (void)c;
  (void)t;
  /*
  float tmin = (min.x - r.orig.x) / r.dir.x;
  float tmax = (max.x - r.orig.x) / r.dir.x;

  if (tmin > tmax) swap(tmin, tmax);

  float tymin = (min.y - r.orig.y) / r.dir.y;
  float tymax = (max.y - r.orig.y) / r.dir.y;

  if (tymin > tymax) swap(tymin, tymax);

  if ((tmin > tymax) || (tymin > tmax))
    return false;

  if (tymin > tmin)
    tmin = tymin;

  if (tymax < tmax)
    tmax = tymax;

  float tzmin = (min.z - r.orig.z) / r.dir.z;
  float tzmax = (max.z - r.orig.z) / r.dir.z;

  if (tzmin > tzmax) swap(tzmin, tzmax);

  if ((tmin > tzmax) || (tzmin > tmax))
    return false;

  if (tzmin > tmin)
    tmin = tzmin;

  if (tzmax < tmax)
    tmax = tzmax;

  return true;*/
  return(0);
}
