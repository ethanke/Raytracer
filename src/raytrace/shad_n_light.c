/*
** shad_n_light.c for raytracing in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 04:01:20 2016 victor sousa
** Last update Thu May  5 03:44:02 2016 Victor Sousa
*/

#include		"main.h"

void			argb_calcul(t_raycast *rcast)
{
  int			i;

  i = -1;
  while (++i < 3)
    {
      rcast->out_col.argb[i] =
      (rcast->out_col.argb[i] +
       min(rcast->out_col.argb[i] + rcast->lambert
	   * (rcast->light_list->intensity/ 255.0) *
	   rcast->mat_touch->color.argb[i], 255)) / 2;
    }
}

float			max_rgb(float a, float b, float c)
{
  return ((a>b)?((a>c)?a:c):((c>b)?c:b));
}

t_cmyk			convert_to_cmyk(t_color in)
{
  t_cmyk		out;
  float			r;
  float			g;
  float			b;

  r = in.argb[RED_CMP] / 255;
  g = in.argb[GREEN_CMP] / 255;
  b = in.argb[BLUE_CMP] / 255;
  out.k = 1 - max_rgb(r, g, b);
  if (out.k == 1)
    {
      out.c = 0;
      out.m = 0;
      out.y = 0;
      return (out);
    }
  out.c = (1 - r - out.k) / (1 - out.k);
  out.m = (1 - g - out.k) / (1- out.k);
  out.y = (1 - b - out.k) / (1 - out.k);
  return (out);
}

void			cmyk_calcul(t_raycast *rcast)
{
  t_cmyk		tmp;
  t_cmyk		in;

  tmp = convert_to_cmyk(rcast->out_col);
  in = convert_to_cmyk(rcast->mat_touch->color);
  tmp.c = (tmp.c + in.c) / 2;
  tmp.m = (tmp.m + in.m) / 2;
  tmp.y = (tmp.y + in.y) / 2;
  tmp.k = (tmp.k + in.k) / 2;
  rcast->out_col.argb[RED_CMP] = 255 * (1 - tmp.c) * (1 - tmp.k);
  rcast->out_col.argb[GREEN_CMP] = 255 * (1 - tmp.m) * (1 - tmp.k);
  rcast->out_col.argb[BLUE_CMP] = 255 * (1 - tmp.y) * (1 - tmp.k);
}

void                    process_shadow(t_prog *prog, t_raycast *rcast)
{
  int			in_shadow;

  in_shadow = 0;
  if ((rcast->obj_touch = hit(prog->obj_list, &rcast->light_ray,
                              &rcast->dist)) != NULL &&
      rcast->obj_touch->obj != NULL)
    in_shadow = 1;
  if (!in_shadow)
    rcast->lambert = mult_vector(rcast->light_ray.dir, rcast->normale) * rcast->coef;
  else
    rcast->lambert = (mult_vector(rcast->light_ray.dir, rcast->normale) * rcast->coef) / 2;
  if (USE_CMYK == 1)
    cmyk_calcul(rcast);
  else
    argb_calcul(rcast);
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
