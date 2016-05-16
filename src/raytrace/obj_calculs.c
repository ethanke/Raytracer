/*
** obj_calculs.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Sun Mar 13 20:30:25 2016 victor sousa
** Last update Mon May 16 13:23:25 2016 Philippe Lefevre
*/

#include		"main.h"
pthread_mutex_t		mutex = PTHREAD_MUTEX_INITIALIZER;

double			fade(double t)
{
  return (t * t * t * (t * (t * 6.0 - 15.0) + 10.0));
}
double			lerp(double t, double a, double b)
{
  return (a + t * (b - a));
}
double			grad(int hash, double x, double y, double z)
{
  int			h;
  double		u;
  double		v;

  h  = hash & 15;
  u = h < 8 || h == 12 || h == 13 ? x : y;
  v = h < 4 || h == 12 || h == 13 ? y : z;
  return (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}

static void		noise_init(int p[512])
{
  noise_init_1(p);
  noise_init_2(p);
  noise_init_3(p);
  noise_init_4(p);
  noise_init_5(p);
  noise_init_6(p);
  noise_init_7(p);
  noise_init_8(p);
  noise_init_9(p);
  noise_init_10(p);
  noise_init_11(p);
  noise_init_12(p);
  noise_init_13(p);
  noise_init_14(p);
  noise_init_15(p);
  noise_init_16(p);
  noise_init_17(p);
  noise_init_18(p);
  noise_init_19(p);
  noise_init_20(p);
  noise_init_21(p);
  noise_init_22(p);
}

double			noise_end(t_noise noise, double x, double y, double z)
{
  int			*p;

  p  = noise.p;
  return (lerp(noise.w, lerp(noise.v, lerp(noise.u, grad(p[noise.AA], x, y, z),
      					   grad(p[noise.BA], x - 1, y, z)),
			     lerp(noise.u, grad(p[noise.AB], x, y - 1, z),
				  grad(p[noise.BB], x - 1, y - 1, z))),
	       lerp(noise.v, lerp(noise.u, grad(p[noise.AA + 1], x, y, z - 1),
				  grad(p[noise.BA + 1], x - 1, y, z - 1)),
		    lerp(noise.u, grad(p[noise.AB + 1], x, y - 1, z - 1),
			 grad(p[noise.BB + 1], x - 1, y - 1, z - 1)))));
}

double			noise(double x, double y, double z)
{
  t_noise		noise;
  int			p[512];

  noise_init(p);
  noise.X = (int)floor(x) & 255;
  noise.Y = (int)floor(y) & 255;
  noise.Z = (int)floor(z) & 255;
  x -= floor(x);
  y -= floor(y);
  z -= floor(z);
  noise.u = fade(x);
  noise.v = fade(y);
  noise.w = fade(z);
  noise.A = p[noise.X] + noise.Y;
  noise.AA = p[noise.A] + noise.Z;
  noise.AB = p[noise.A + 1] + noise.Z;
  noise.B = p[noise.X + 1] + noise.Y;
  noise.BA = p[noise.B] + noise.Z;
  noise.BB = p[noise.B + 1] + noise.Z;
  noise.p = p;
  return (noise_end(noise, x, y, z));
}

int 			calc_normale_beg(t_prog *prog, t_raycast *rcast,
					 t_coord *noiseCoef)
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
  noiseCoef->x = noise(0.1 * rcast->new_point.x, 0.1
		      * rcast->new_point.y, 0.1 * rcast->new_point.z);
  noiseCoef->y = noise(0.1 * rcast->new_point.y, 0.1
		      * rcast->new_point.z, 0.1 * rcast->new_point.x);
  noiseCoef->z = noise(0.1 * rcast->new_point.z, 0.1
      		      * rcast->new_point.x, 0.1 * rcast->new_point.y);
  return (0);
}

int			calc_normale(t_prog *prog, t_raycast *rcast)
{
  t_coord		noiseCoef;
  float			temp;

  pthread_mutex_lock(&mutex);
  if (calc_normale_beg(prog, rcast, &noiseCoef))
    return (-1);
  rcast->normale.x = (1.0f - rcast->mat_touch->bump)
    * rcast->normale.x + rcast->mat_touch->bump * noiseCoef.x;
  rcast->normale.y = (1.0f - rcast->mat_touch->bump)
    * rcast->normale.y + rcast->mat_touch->bump * noiseCoef.y;
  rcast->normale.z = (1.0f - rcast->mat_touch->bump)
    * rcast->normale.z + rcast->mat_touch->bump * noiseCoef.z;
  pthread_mutex_unlock(&mutex);
  temp = mult_vector(rcast->normale, rcast->normale);
  if (temp == 0.0)
    return (-1);
  temp = invsqrtf(temp);
  rcast->normale = float_time_vector(temp, rcast->normale);
  return (0);
}

int			damier(t_coord *pos)
{
  t_point		tmp;

  tmp.x = (int)((pos->x + 13000) / SIZE_TILE);
  tmp.y = (int)(pos->y / SIZE_TILE);
  tmp.z = (int)((pos->z + 13000) / SIZE_TILE);
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
  t_coord		vn;
  t_coord		ve;
  t_coord		vp;
  float 		u;
  float 		v;
  float			phi;
  float			theta;

  rcast->sphere = rcast->obj_touch->obj;
  rcast->mat_touch = get_color(rcast->sphere->material, prog->mat_list);
  rcast->new_point = add_vector(rcast->ray.start,
				float_time_vector(rcast->dist,
						  rcast->ray.dir));
  rcast->normale = minus_vector(rcast->new_point, rcast->sphere->center);
  vn.x = 0;
  vn.y = - 1;
  vn.z = 0;
  vn = normalize(vn);

  ve.x = -1;
  ve.y = 0;
  ve.z = 0;
  ve = normalize(ve);

  vp = minus_vector(rcast->new_point, rcast->sphere->center);
  vp = normalize(vp);
  if (!my_strstr(rcast->mat_touch->texture_path, "NULL"))
    {

      phi = acos(-mult_vector(vn, vp));
      v = phi / M_PI;
      theta = (acos(mult_vector(vp, ve) / sin(phi))) / (2.0 * M_PI);
      if (vp.z < 0.01 && vp.z > -0.01)
	theta = 0;
      if (mult_vector(crossProduct(vn, ve), vp) > 0)
	u = theta;
      else
	u = 1 - theta;
      v = v * (float)rcast->mat_touch->texture->height;
      u = u * (float)rcast->mat_touch->texture->width;
      if (v >= rcast->mat_touch->texture->height)
	v = 1;
      if (u >= rcast->mat_touch->texture->width)
        u = 1;
      rcast->mat_touch->color =
	rcast->mat_touch->texture->color[(int)v][(int)u];
    }
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
  rcast->normale.x = -rcast->plan->dir.x;
  rcast->normale.y = -rcast->plan->dir.y;
  rcast->normale.z = -rcast->plan->dir.z;
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
  rcast->normale =
  minus_vector(co, (float_time_vector((mult_vector(co, rcast->cyl->dir) /
				       mult_vector(rcast->cyl->dir,
						   rcast->cyl->dir)),
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
