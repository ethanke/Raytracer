/*
** reflect.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 04:04:48 2016 victor sousa
** Last update Mon Apr 25 06:41:51 2016 Victor Sousa
*/

#include		"main.h"

void                    process_reflect(t_raycast *rcast)
{
  rcast->coef *= rcast->mat_touch->reflect / 100.0;
  rcast->reflect = 2.0 * mult_vector(rcast->ray.dir, rcast->normale);
  rcast->ray.start = rcast->new_point;
  rcast->ray.dir = minus_vector(rcast->ray.dir,
				float_time_vector(rcast->reflect,
						  rcast->normale));
  rcast->depth++;
}

int                     reflect_loop(t_prog *prog, t_raycast *rcast)
{
  float			tmp;

  if ((rcast->obj_touch = hit(prog->obj_list,
                              &rcast->ray, &rcast->dist)) == NULL ||
      rcast->obj_touch->obj == NULL)
    return (-1);
  if (rcast->obj_touch->type == 's')
    calc_sphere_normale(prog, rcast);
  else if (rcast->obj_touch->type == 't')
    calc_triangle_normale(prog, rcast);
  free(rcast->obj_touch);
  tmp = mult_vector(rcast->normale, rcast->normale);
  if (tmp == 0)
    return (-1);
  tmp = 1.0 / sqrt(tmp);
  rcast->normale = float_time_vector(tmp, rcast->normale);
  rcast->light_list = prog->light_list;
  while (rcast->light_list != NULL)
    process_light(prog, rcast);
  process_reflect(rcast);
  return (0);
}
