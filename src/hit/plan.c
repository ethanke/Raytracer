/*
** plan.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Wed Apr 27 16:59:30 2016 Victor Sousa
** Last update Thu Apr 28 02:41:16 2016 Gaëtan Léandre
*/

#include		"main.h"

int			hit_plan(t_ray *r, t_plan *p, float *t)
{
  float			a;
  float			b;
  float			dist;

  a = p->dir.x * r->dir.x +
      p->dir.y * r->dir.y + p->dir.z * r->dir.z;
  b = p->dir.x * (r->start.x - p->center.x) +
      p->dir.y * (r->start.y - p->center.y) +
  p->dir.z * (r->start.z - p->center.z) - (p->dir.x * p->center.x +
	      p->dir.y * p->center.y + p->dir.z * p->center.z);
  if (a == 0)
    return (0);
  dist = -(b / a);
  if (dist > 0.1 && *t > dist)
    {
      *t = dist;
      return (1);
    }
  return (0);
}
