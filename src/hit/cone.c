/*
** cone.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri Apr 29 05:28:00 2016 Victor Sousa
** Last update Wed May  4 02:37:51 2016 Victor Sousa
*/

#include		"main.h"

int 			hit_circle(t_ray *r, t_circle *c, float *t)
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
  t_coord		temp;

  fac = (c->radius * c->radius) / (double) (c->height * c->height);
  y.x = (fac) * r->dir.y * r->dir.y;
  y.y = (2.0 * fac * r->start.y * r->dir.y) - (2.0 *
	 (c->radius * c->radius) / c->height) * r->dir.y;
  y.z = (fac * r->start.y * r->start.y) - ((2.0 * (c->radius * c->radius) /
					   c->height) * r->start.y) +
  (c->radius * c->radius);
  x.x = (r->dir.x * r->dir.x) + (r->dir.z * r->dir.z) - y.x;
  x.y = (2.0 * r->start.x * r->dir.x) + (2.0 * r->start.z * r->dir.z) - y.y;
  x.z = (r->start.x * r->start.x) + (r->start.z * r->start.z) - y.z;
  d = (x.y * x.y) - (4.0 * x.x * x.z);
  if (d >= 0)
    {
      dist[0] = (-x.y - sqrt(d)) / (2.0 * x.x);
      dist[1] = (-x.y + sqrt(d)) / (2.0 * x.x);
      if (dist[1] < dist[0] && dist[1] > 0.1)
	{
	  temp = add_vector(r->start, float_time_vector(dist[1], r->dir));
	  if (temp.y <= c->height && temp.y >= 0.0 && dist[1] < *t)
	    {
	      *t = dist[1];
	      return (1);
	    }
	}
      else if (dist[1] > dist[0] && dist[0] > 0.1)
	{
	  temp = add_vector(r->start, float_time_vector(dist[0], r->dir));
	  if (temp.y <= c->height && temp.y >= 0.0 && dist[0] < *t)
	    {
	      *t = dist[0];
	      return (1);
	    }
	}
    }
  return(0);
  /* TEST 2 */
  /*
  t_coord rayOrigin = r->start;
  t_coord rayDirection = r->dir;
  t_coord pa = add_vector(co->center, float_time_vector(co->height, co->dir));
  t_coord va = float_time_vector(-1, co->dir);
  t_coord deltaP = minus_vector(rayOrigin, pa);
  double c1 = mult_vector(rayDirection, va);
  t_coord c2 = float_time_vector(c1, va);
  double c3 = mult_vector(deltaP, va);
  t_coord c4 = float_time_vector(c3, va);
  double alpha = atan(co->radius / co->height);
  double cos2a = cos(alpha) * cos(alpha);

  double sin2a = 1 - cos2a;
  double a = cos2a * mult_vector(minus_vector(rayDirection, c2), minus_vector(rayDirection, c2)) - sin2a * c1 * c1;
  double b = 2 * cos2a * mult_vector(minus_vector(rayDirection, c2), minus_vector(deltaP, c4)) - 2 * sin2a * (c1 * c3);
  double c = cos2a * mult_vector(minus_vector(deltaP, c4), minus_vector(deltaP, c4)) - sin2a * (c3 * c3);
  double discriminant = b * b - 4 * a * c;
  double t1, t2;
  if (discriminant < 0)
    return (0);
  else
    {
      discriminant = sqrt(discriminant);
      t1 = ((-1 * b) + discriminant) / (2 * a);
      t2 = ((-1 * b) - discriminant) / (2 * a);
      if (t1 < t2 && t1 >= 0.1)
	{
	  if (mult_vector(co->dir, add_vector(minus_vector(rayOrigin, co->center), float_time_vector(t1, rayDirection))) > 0 &&
	      mult_vector(co->dir, add_vector(minus_vector(rayOrigin, pa), float_time_vector(t1, rayDirection))) > 0)
	    {
	      if (t1 < *t)
		{
		  *t = t1;
		  return (1);
		}
	    }
	}
      else if (t2 >= 0.1)
	{
	  if (mult_vector(co->dir, add_vector(minus_vector(rayOrigin, co->center), float_time_vector(t2, rayDirection))) > 0 &&
	      mult_vector(co->dir, add_vector(minus_vector(rayOrigin, pa), float_time_vector(t2, rayDirection))) > 0)
	    {
	      if (t2 < *t)
		{
		  *t = t2;
		  return (1);
		}
	    }
	}
    }
  return (0);
  */
}
