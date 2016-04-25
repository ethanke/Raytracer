/*
** obj_calculs.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Sun Mar 13 20:30:25 2016 victor sousa
** Last update Mon Apr 25 02:32:53 2016 victor sousa
*/

#include		"main.h"

void			calc_sphere_normale(t_prog *prog, t_raycast *rcast)
{
  rcast->sphere = rcast->obj_touch->obj;
  rcast->mat_touch = get_sphere_color(rcast->sphere->material,
				      prog->mat_list);
  rcast->tmp_coord = float_time_vector(rcast->dist, rcast->ray.dir);
  rcast->new_point = add_vector(rcast->ray.start, rcast->tmp_coord);
  rcast->normale = minus_vector(rcast->new_point, rcast->sphere->center);
}
