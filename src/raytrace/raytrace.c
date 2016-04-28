/*
** raytrace.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 01:01:17 2016 victor sousa
** Last update Thu Apr 28 07:06:25 2016 Victor Sousa
*/

#include		"main.h"

void			init_ray(t_bunny_position *win_size, t_ray *ray,
				 t_bunny_position *pos, t_prog *prog)
{
  t_coord		center;
  t_coord		point;

  ray->start.x = prog->cam_pos.x;
  ray->start.y = prog->cam_pos.y;
  ray->start.z = prog->cam_pos.z;
  center.x = ray->start.x + 1000 * prog->cam_dir.x;
  center.y = ray->start.y + 1000 * prog->cam_dir.y;
  center.z = ray->start.z + 1000 * prog->cam_dir.z;
  point.x = center.x - (win_size->x / 2);
  point.y = center.y - (win_size->y / 2);
  point.z = center.z;
  point.x += pos->x;
  point.y += pos->y;
  ray->dir.x = point.x - ray->start.x;
  ray->dir.y = point.y - ray->start.y;
  ray->dir.z = point.z - ray->start.z;
  ray->dir = normalize(ray->dir);
}

int			raytrace_loop(t_prog *prog, t_raycast *rcast,
				      t_bunny_position *pos)
{
  init_ray(&prog->win_size, &rcast->ray, pos, prog);
  rcast->depth = 0;
  rcast->coef = 1.0f;
  rcast->out_col.full = 0xff000000;
  while ((rcast->coef > 0.0f) && (rcast->depth < 10))
    {
      rcast->dist = 20000;
      if (reflect_loop(prog, rcast) != 0)
	rcast->depth = 25;
    }
  tekpixel(prog->pix, pos, &rcast->out_col);
  return (0);
}

int			raytrace(t_prog *prog)
{
  t_bunny_position      pos;
  t_raycast		raycast;

  my_putstr("\nRaytracing started\n");
  pos.y = -1;
  while (++pos.y < prog->win_size.y)
    {
      pos.x = -1;
      while (++pos.x < prog->win_size.x)
	raytrace_loop(prog, &raycast, &pos);
    }
  my_putstr("Raytracing successfull\n");
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
  bunny_display(prog->win);
  return (0);
}
