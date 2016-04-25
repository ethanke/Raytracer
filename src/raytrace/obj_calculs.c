/*
** obj_calculs.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Sun Mar 13 20:30:25 2016 victor sousa
** Last update Mon Apr 25 06:40:01 2016 Victor Sousa
*/

#include		"main.h"

void			calc_sphere_normale(t_prog *prog, t_raycast *rcast)
{
  rcast->sphere = rcast->obj_touch->obj;
  rcast->mat_touch = get_sphere_color(rcast->sphere->material,
				      prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  rcast->normale = minus_vector(rcast->new_point, rcast->sphere->center);
}

t_coord			triangle_normale(t_triangle *tr)
{
  t_coord 		e1;
  t_coord 		e2;
  t_coord 		h;

  e1 = minus_vector(tr->angle[1], tr->angle[0]);
  e2 = minus_vector(tr->angle[2], tr->angle[0]);
  h = crossProduct(e2, e1);
  return (h);
}

void			calc_triangle_normale(t_prog *prog, t_raycast *rcast)
{
  rcast->triangle = rcast->obj_touch->obj;
  rcast->mat_touch = get_sphere_color(rcast->triangle->material,
				      prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  rcast->normale = triangle_normale(rcast->triangle);
}
