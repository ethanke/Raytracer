/*
** cone.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri Apr 29 05:28:00 2016 Victor Sousa
** Last update Fri Apr 29 09:30:47 2016 Victor Sousa
*/

#include		"main.h"

bool intersect_circle(t_ray *r, t_circle *c)
{
  float t = 2000;

  if (hit_plan(r, &c->plan, &t))
    {
      t_coord p = add_vector(r->start, float_time_vector(t, r->dir));
      t_coord v = minus_vector(c->plan.center, p);
      float d2 = mult_vector(v, v);
      if (d2 <= c->radius * c->radius)
	return (t);
    }
  return (-1);
}

int			hit_cone(t_ray *r, t_cone *c, float *t, t_raycast *rcast)
{
  double 		dist[2];
  double		fac;
  t_coord		x;
  t_coord		y;
  double		d;
  int			i;
  t_circle		base;

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
	  t_coord temp;
	  temp = add_vector(r->start, float_time_vector(dist[i], r->dir));
	  if (temp.y <= c->height && temp.y >= 0 && dist[i] < *t)
	    {
	      *t = dist[i];
	      return (1);
	    }
	  i++;
	}
    }
  base.plan.center.x = c->center.x;
  base.plan.center.y = c->center.y;
  base.plan.center.z = c->center.z;
  base.plan.dir.x = c->dir.x;
  base.plan.dir.y = c->dir.y;
  base.plan.dir.z = c->dir.z;
  base.radius = c->radius;
  if ((dist[0] = intersect_circle(r, &base)) > 0)
    {
      if (dist[0] < *t)
	{
	  *t = dist[0];
	  rcast->touch_circle = 1;
	  return (1);
	}
    }
  return (0);
}
