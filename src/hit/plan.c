/*
** plan.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Wed Apr 27 16:59:30 2016 Victor Sousa
** Last update Wed Apr 27 18:27:21 2016 Victor Sousa
*/

#include		"main.h"

int			hit_plan(t_ray *r, t_plan *p, float *t)
{
  float			denom;
  float			dist;

  denom = mult_vector(p->dir, r->dir);
  if (ABS(denom) > 0.1f)
    {
      dist = mult_vector(minus_vector(p->center, r->start), p->dir) / denom;
      if (dist >= 0 && dist < *t)
	{
	  *t = dist;
	  return (1);
	}
    }
  return (0);
}
