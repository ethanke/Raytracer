/*
** obj_calculs.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Sun Mar 13 20:30:25 2016 victor sousa
** Last update Wed May  4 18:35:24 2016 Victor Sousa
*/

#include		"main.h"

int			calc_normale(t_prog *prog, t_raycast *rcast)
{
  if (rcast->obj_touch->type == 's')
    calc_sphere_normale(prog, rcast);
  else if (rcast->obj_touch->type == 't')
    calc_triangle_normale(prog, rcast);
  else if (rcast->obj_touch->type == 'p')
    calc_plan_normale(prog, rcast);
  else if (rcast->obj_touch->type == 'c')
    calc_cone_normale(prog, rcast);
  else if (rcast->obj_touch->type == 'y')
    calc_cyl_normale(prog, rcast);
  else if (rcast->obj_touch->type == 'i')
    calc_circle_normale(prog, rcast);
  else
    return (-1);
  return (0);
}

int			damier(t_coord *pos)
{
  t_point		tmp;

  tmp.x = (int)((pos->x + 13272) / SIZE_TILE);
  tmp.y = (int)(pos->y / SIZE_TILE);
  tmp.z = (int)((pos->z + 13272) / SIZE_TILE);
  if (tmp.x % 2 == 0)
    {
      if (((tmp.y % 2 == 0) && (tmp.z % 2 == 0)) ||
	  (((tmp.y % 2 != 0) && (tmp.z % 2 != 0))))
	return (0);
      else
	return (1);
    }
  else
    {
      if ((((tmp.y % 2 == 0) && (tmp.z % 2 == 0))) ||
	  (((tmp.y % 2 != 0) && (tmp.z % 2 != 0))))
	return (1);
      else
	return (0);
  }
}

void			calc_sphere_normale(t_prog *prog, t_raycast *rcast)
{
  rcast->sphere = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->sphere->material, prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  rcast->normale = minus_vector(rcast->new_point, rcast->sphere->center);
}

void			calc_triangle_normale(t_prog *prog, t_raycast *rcast)
{
  t_coord 		e1;
  t_coord 		e2;
  t_coord 		h;

  rcast->triangle = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->triangle->material,
				      prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  e1 = minus_vector(rcast->triangle->angle[1], rcast->triangle->angle[0]);
  e2 = minus_vector(rcast->triangle->angle[2], rcast->triangle->angle[0]);
  h = crossProduct(e2, e1);
  if (h.x >= 0 || h.y >= 0 || h.z >= 0)
    h = crossProduct(e1, e2);
  rcast->normale = h;
}

void			calc_plan_normale(t_prog *prog, t_raycast *rcast)
{
  t_coord		dist_to_center;

  rcast->plan = rcast->obj_touch->obj;
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  rcast->normale = rcast->plan->dir;
  dist_to_center = minus_vector(rcast->new_point, rcast->plan->center);
  if (damier(&dist_to_center) == 0)
    rcast->mat_touch = get_color(rcast->plan->material, prog->mat_list);
  else
    rcast->mat_touch = get_color(rcast->plan->material2, prog->mat_list);
}

void			calc_cone_normale(t_prog *prog, t_raycast *rcast)
{
  t_coord		top;
  t_coord		perp;

  rcast->cone = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->cone->material, prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));

  top = add_vector(rcast->cone->center, float_time_vector(rcast->cone->height,
							  rcast->cone->dir));
  perp = crossProduct(rcast->cone->dir, minus_vector(rcast->new_point, top));
  rcast->normale = normalize(crossProduct(minus_vector(rcast->new_point, top),
					  perp));
}

void			calc_cyl_normale(t_prog *prog, t_raycast *rcast)
{
  t_coord		co;

  rcast->cyl = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->cyl->material, prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  co = minus_vector(rcast->new_point, rcast->cyl->center);
  rcast->normale = minus_vector(co, (float_time_vector((mult_vector(co, rcast->cyl->dir) /
							mult_vector(rcast->cyl->dir, rcast->cyl->dir)),
						       rcast->cyl->dir)));
}

void			calc_circle_normale(t_prog *prog, t_raycast *rcast)
{
  rcast->circle = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->circle->material, prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  rcast->normale = rcast->circle->plan.dir;
}
