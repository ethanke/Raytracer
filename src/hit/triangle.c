/*
** triangle.c for  in /home/sousa_v/rendu/lapin/raytracer_temp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Mon Apr 25 04:34:58 2016 Victor Sousa
** Last update Tue Apr 26 00:57:50 2016 Gaëtan Léandre
*/

#include		"main.h"

int			hit_triangle(t_ray *r, t_triangle *tr, float *old_dist)
{
  t_coord 		e1,e2,h,s,q;
  float 		a,f,u,v,t;

  e1 = minus_vector(tr->angle[1], tr->angle[0]);
  e2 = minus_vector(tr->angle[2], tr->angle[0]);
  h = crossProduct(r->dir, e2);
  a = mult_vector(e1, h);
  if (a > -0.00001 && a < 0.00001)
    return (0);
  f = 1 / a;
  s = minus_vector(r->start, tr->angle[0]);
  u = f * (mult_vector(s, h));
  if (u < 0.0 || u > 1.0)
    return (0);
  q = crossProduct(s, e1);
  v = f * mult_vector(r->dir, q);
  if (v < 0.0 || u + v > 1.0)
    return (0);
  t = f * mult_vector(e2, q);
  if (t > 0.1)
    {
      *old_dist = t;
      return (1);
    }
  return (0);
}
