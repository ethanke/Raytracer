/*
** cylinder.c for  in /home/sousa_v/rendu/lapin/rtv2/src/hit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Tue May  3 02:58:39 2016 Victor Sousa
** Last update Tue May  3 11:34:16 2016 Victor Sousa
*/

#include		"main.h"

int 			hit_cylin(t_ray *r, t_cylin *cy, float *t)
{
  t_coord alpha = float_time_vector(mult_vector(r->dir, cy->dir), cy->dir);
  t_coord deltaP = minus_vector(r->start, cy->center);
  t_coord beta = float_time_vector(mult_vector(deltaP, cy->dir), cy->dir);
  t_coord center2 = add_vector(cy->center, float_time_vector(cy->height, cy->dir));
  double a = mult_vector(minus_vector(r->dir, alpha), minus_vector(r->dir, alpha));
  double b = 2 * mult_vector(minus_vector(r->dir, alpha), minus_vector(deltaP, beta));
  double c = mult_vector(minus_vector(deltaP, beta), minus_vector(deltaP, beta)) - cy->radius * cy->radius;
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
	  if (mult_vector(cy->dir, add_vector(minus_vector(r->start, cy->center), float_time_vector(t1, r->dir))) > 0 &&
	      mult_vector(cy->dir, add_vector(minus_vector(r->start, center2), float_time_vector(t1, r->dir))) < 0)
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
	  if (mult_vector(cy->dir, add_vector(minus_vector(r->start, cy->center), float_time_vector(t2, r->dir))) > 0 &&
	      mult_vector(cy->dir, add_vector(minus_vector(r->start, center2), float_time_vector(t2, r->dir))) < 0)
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
}
