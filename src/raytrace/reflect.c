/*
** reflect.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 04:04:48 2016 victor sousa
** Last update Tue May  3 11:34:05 2016 Victor Sousa
*/

#include		"main.h"

void                    process_reflect(t_raycast *rcast)
{
  rcast->coef = rcast->coef * (rcast->mat_touch->reflect / 100.0);
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

  rcast->dist = 20000;
  if ((rcast->obj_touch = hit(prog->obj_list,
                              &rcast->ray, &rcast->dist, rcast)) == NULL ||
      rcast->obj_touch->obj == NULL)
    return (-1);
  if (rcast->depth == 0 && rcast->coef == 1.0)
    rcast->out_col.full = 0xFF000000;
  if (calc_normale(prog, rcast) == -1)
    return (-1);
  tmp = mult_vector(rcast->normale, rcast->normale);
  if (tmp == 0)
    return (-1);
  free(rcast->obj_touch);
  tmp = 1.0 / sqrt(tmp);
  rcast->normale = float_time_vector(tmp, rcast->normale);
  rcast->light_list = prog->light_list;
  while (rcast->light_list != NULL)
    process_light(prog, rcast);
  process_reflect(rcast);
  return (0);
}
