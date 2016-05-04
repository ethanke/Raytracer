/*
** plan.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Wed Apr 27 16:59:30 2016 Victor Sousa
** Last update Wed May  4 19:51:28 2016 Victor Sousa
*/

#include		"main.h"

int			hit_plan(t_ray *r, t_plan *p, float *t)
{
  float			dist;

  dist = - (mult_vector(p->dir, r->start) / mult_vector(p->dir, r->dir));
  if (dist > 0.1 && *t > dist)
    {
      *t = dist;
      return (1);
    }
  return (0);
}
