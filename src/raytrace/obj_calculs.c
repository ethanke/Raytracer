/*
** obj_calculs.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Sun Mar 13 20:30:25 2016 victor sousa
** Last update Sun May  1 22:17:42 2016 Victor Sousa
*/

#include		"main.h"

int			calc_normale(t_prog *prog, t_raycast *rcast, t_ray *ray, t_color *col)
{
  if (rcast->obj_touch->type == 's')
    calc_sphere_normale(prog, rcast, ray);
  else if (rcast->obj_touch->type == 't')
    calc_triangle_normale(prog, rcast, ray);
  else if (rcast->obj_touch->type == 'p')
    calc_plan_normale(prog, rcast, ray);
  else if (rcast->obj_touch->type == 'c')
    calc_cone_normale(prog, rcast, ray);
  else
    return (-1);
  col->full = rcast->mat_touch->color.full;
  return (0);
}

void			calc_sphere_normale(t_prog *prog, t_raycast *rcast, t_ray *ray)
{
  rcast->sphere = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->sphere->material, prog->mat_list);
  rcast->hit_point = add_vector(ray->start,
				float_time_vector(rcast->hit_dist,
						  ray->dir));
  rcast->normale = minus_vector(rcast->hit_point, rcast->sphere->center);
}

void			calc_triangle_normale(t_prog *prog, t_raycast *rcast, t_ray *ray)
{
  t_coord 		e1;
  t_coord 		e2;
  t_coord 		h;

  rcast->triangle = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->triangle->material,
				      prog->mat_list);
  rcast->hit_point = add_vector(ray->start,
				float_time_vector(rcast->hit_dist,
						  ray->dir));
  e1 = minus_vector(rcast->triangle->angle[1], rcast->triangle->angle[0]);
  e2 = minus_vector(rcast->triangle->angle[2], rcast->triangle->angle[0]);
  h = crossProduct(e2, e1);
  if (h.x >= 0 || h.y >= 0 || h.z >= 0)
    h = crossProduct(e1, e2);
  rcast->normale = h;
}

void			calc_plan_normale(t_prog *prog, t_raycast *rcast, t_ray *ray)
{
  rcast->plan = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->plan->material, prog->mat_list);
  rcast->hit_point = add_vector(ray->start,
				float_time_vector(rcast->hit_dist,
						  ray->dir));
  rcast->normale = rcast->plan->dir;
}

void			calc_cone_normale(t_prog *prog, t_raycast *rcast, t_ray *ray)
{
  float			mag;
  float			costheta;

  rcast->cone = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->cone->material, prog->mat_list);
  rcast->hit_point = add_vector(ray->start,
				float_time_vector(rcast->hit_dist,
						  ray->dir));
  if (rcast->touch_circle == 1)
    {
      rcast->normale = rcast->cone->dir;
      rcast->touch_circle = 0;
    }
  else
   {
      mag = sqrt(rcast->hit_point.x * rcast->hit_point.x + rcast->hit_point.z *
		 rcast->hit_point.z);
      costheta = rcast->hit_point.x / mag;
      rcast->normale.x = 1.0f / sqrt(2.0f) * costheta;
      rcast->normale.y = 1.0f / sqrt(2.0f);
      rcast->normale.z = 1.0f / sqrt(2.0f) * (1.0 - costheta);
    }
}
