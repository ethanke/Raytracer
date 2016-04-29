/*
** cone.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri Apr 29 05:28:00 2016 Victor Sousa
** Last update Fri Apr 29 18:47:23 2016 Victor Sousa
*/

#include		"main.h"

int 			hit_circle(t_ray *r, t_circle *c, float *t, t_raycast *rcast)
{
  float			dist;

  dist = *t;
  if (hit_plan(r, &c->plan, &dist))
    {
      t_coord p = add_vector(r->start, float_time_vector(dist, r->dir));
      t_coord v = minus_vector(p, c->plan.center);
      float d2 = mult_vector(v, v);
      if (d2 < c->radius * c->radius)
	{
	  if (dist < *t)
	    {
	      *t = dist;
	      rcast->touch_circle = 1;
	      return (1);
	    }
	}
    }
  return (0);
}

int			hit_cone(t_ray *r, t_cone *c, float *t)
{
  double 		dist[2];
  double		fac;
  t_coord		x;
  t_coord		y;
  double		d;
  int			i;

  fac = (c->radius * c->radius) / (double) (c->height * c->height);
  y.x = (fac) * r->dir.y * r->dir.y;
  y.y = (2 * fac * r->start.y * r->dir.y) - (2 *
	 (c->radius * c->radius) / c->height) * r->dir.y;
  y.z = (fac * r->start.y * r->start.y) - ((2 * (c->radius * c->radius) /
					   c->height) * r->start.y) +
  (c->radius * c->radius);
  x.x = (r->dir.x * r->dir.x) + (r->dir.z * r->dir.z) - y.x;
  x.y = (2 * r->start.x * r->dir.x) + (2 * r->start.z * r->dir.z) - y.y;
  x.z = (r->start.x * r->start.x) + (r->start.z * r->start.z) - y.z;
  d = (x.y * x.y) - (4 * x.x * x.z);
  i = 0;
  if (d >= 0)
    {
      dist[0] = (-x.y - sqrt(d)) / (2 * x.x);
      dist[1] = (-x.y + sqrt(d)) / (2 * x.x);
      while (i < 2)
	{
	  if (dist[i] > 0.1)
	    {
	      t_coord temp;
	      temp = add_vector(r->start, float_time_vector(dist[i], r->dir));
	      if (temp.y <= c->height && temp.y >= 0 && dist[i] < *t)
		{
		  *t = dist[i];
		  return (1);
		}
	    }
	  i++;
	}
    }
  return(0);
}
