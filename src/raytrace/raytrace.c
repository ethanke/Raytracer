/*
** raytrace.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 01:01:17 2016 victor sousa
** Last update Sat Apr 30 16:38:25 2016 Victor Sousa
*/

#include		"main.h"

void			init_ray(t_bunny_position *win_size, t_ray *ray,
				 t_bunny_position *pos, t_prog *prog)
{
  t_coord		point;
  t_coord 		ang;

  ray->start.x = prog->cam_pos.x;
  ray->start.y = prog->cam_pos.y;
  ray->start.z = prog->cam_pos.z;
  ang.x = prog->cam_rot.x - ((float)prog->cam_fov.x / (float)win_size->x) * (pos->x - win_size->x / 2);
  ang.y = prog->cam_rot.y - ((float)prog->cam_fov.y / (float)win_size->y) * (pos->y - win_size->y / 2);
  point.x = ray->start.x + cos(DTR(ang.x));
  point.y = ray->start.y + sin(DTR(ang.y));
  point.z = ray->start.z + sin(DTR(ang.x));
  ray->dir = normalize(minus_vector(point, ray->start));
}

void			init_ray_for_transpa(t_prog *prog, t_raycast *rcast)
{
  rcast->ray.start = add_vector(rcast->ray.start, float_time_vector(rcast->dist + 0.1, rcast->ray.dir));
  if (hit(prog->obj_list, &rcast->ray, &rcast->dist, rcast))
    rcast->ray.start = add_vector(rcast->ray.start, float_time_vector(rcast->dist + 0.1, rcast->ray.dir));
}

void			raytrace_loop(t_prog *prog, t_raycast *rcast)
{
  float			tmp;

  rcast->depth = 0;
  rcast->coef = 1.0f;
  rcast->out_col.full = 0xff000000;
  rcast->mat_touch = NULL;
  while ((rcast->coef > 0.0f) && (rcast->depth < 10))
    {
      rcast->dist = 20000;
      if ((rcast->obj_touch = hit(prog->obj_list,
                                  &rcast->ray, &rcast->dist, rcast)) == NULL ||
          rcast->obj_touch->obj == NULL)
        break;
      if (rcast->obj_touch->type == 's')
        calc_sphere_normale(prog, rcast);
      else if (rcast->obj_touch->type == 't')
        calc_triangle_normale(prog, rcast);
      else if (rcast->obj_touch->type == 'p')
        calc_plan_normale(prog, rcast);
      else if (rcast->obj_touch->type == 'c')
        calc_cone_normale(prog, rcast);
      else
        break;
      free(rcast->obj_touch);
      tmp = mult_vector(rcast->normale, rcast->normale);
      if (tmp == 0)
	break;
      tmp = 1.0 / sqrt(tmp);
      rcast->normale = float_time_vector(tmp, rcast->normale);
      rcast->light_list = prog->light_list;
      while (rcast->light_list != NULL)
        process_light(prog, rcast);
      process_reflect(rcast);
    }
}

void			process_transpa(t_prog *prog, t_raycast *rcast)
{
  init_ray_for_transpa(prog, rcast);
  raytrace_loop(prog, rcast);
}

int			raytrace(t_prog *prog)
{
  t_bunny_position      pos;
  t_raycast		raycast;

  my_putstr("\nRaytracing started\n");
  raycast.touch_circle = 0;
  pos.y = -1;
  while (++pos.y < prog->win_size.y)
    {
      pos.x = -1;
      while (++pos.x < prog->win_size.x)
	{
	  init_ray(&prog->win_size, &raycast.ray, &pos, prog);
	  raytrace_loop(prog, &raycast);
	  tekpixel(prog->pix, &pos, &raycast.out_col);
	}
      bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
      bunny_display(prog->win);
    }
  my_putstr("Raytracing successfull\n");
  return (0);
}
