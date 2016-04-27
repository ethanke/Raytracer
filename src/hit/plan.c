/*
** plan.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Wed Apr 27 16:59:30 2016 Victor Sousa
** Last update Wed Apr 27 17:00:42 2016 Victor Sousa
*/

#include		"main.h"

int			hit_plan(t_ray *r, t_plan *p, float *t)
{
  float dotProdut = Vector3.Dot(this.normal, ray.dirVector);

  if (dotProdut > 0.0f)
    {
      float dist = -(Vector3.Dot(this.normal, ray.startPoint) + this.planDist) / dotProdut;
      if (dist > 0.0f && dist < *t)
	{
	  *t = dist;
	  return (1);
	}
    }
  return (0);
}
