/*
** shad_n_light.c for raytracing in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 04:01:20 2016 victor sousa
** Last update Wed Apr 27 20:02:30 2016 Victor Sousa
*/

#include		"main.h"

void                    process_shadow(t_prog *prog, t_raycast *rcast)
{
  rcast->in_shadow = 0;
  if ((rcast->obj_touch = hit(prog->obj_list, &rcast->light_ray,
                              &rcast->dist)) != NULL &&
      rcast->obj_touch->obj != NULL)
    rcast->in_shadow = 1;
  if (!rcast->in_shadow)
    rcast->lambert = mult_vector(rcast->light_ray.dir, rcast->normale)
      * rcast->coef;
  else
    rcast->lambert = (mult_vector(rcast->light_ray.dir, rcast->normale)
		      * rcast->coef) / 2;

  rcast->out_col.argb[RED_CMP] =
  (rcast->out_col.argb[RED_CMP] +
   min(rcast->out_col.argb[RED_CMP] + rcast->lambert
       * (rcast->light_list->intensity/ 255.0) *
       rcast->mat_touch->color.argb[RED_CMP], 255)) / 2;
  rcast->out_col.argb[GREEN_CMP] =
  (rcast->out_col.argb[GREEN_CMP] +
   min(rcast->out_col.argb[GREEN_CMP] + rcast->lambert
       * (rcast->light_list->intensity / 255.0) *
       rcast->mat_touch->color.argb[GREEN_CMP], 255)) / 2;
  rcast->out_col.argb[BLUE_CMP] =
  (rcast->out_col.argb[BLUE_CMP] +
   min(rcast->out_col.argb[BLUE_CMP] + rcast->lambert *
       (rcast->light_list->intensity / 255.0) *
       rcast->mat_touch->color.argb[BLUE_CMP], 255)) / 2;
  free(rcast->obj_touch);
}

int                     process_light(t_prog *prog, t_raycast *rcast)
{
  rcast->dist_vector = minus_vector(rcast->light_list->center,
                                    rcast->new_point);
  if (mult_vector(rcast->dist_vector, rcast->normale) <= 0.0)
    {
      rcast->light_list = rcast->light_list->next;
      return (-1);
    }
  rcast->dist = sqrt(mult_vector(rcast->dist_vector, rcast->dist_vector));
  if (rcast->dist <= 0.0)
    {
      rcast->light_list = rcast->light_list->next;
      return (-1);
    }
  rcast->light_ray.start = rcast->new_point;
  rcast->light_ray.dir = float_time_vector((1.0 / rcast->dist),
                                           rcast->dist_vector);

  process_shadow(prog, rcast);
  rcast->light_list = rcast->light_list->next;
  return (0);
}
