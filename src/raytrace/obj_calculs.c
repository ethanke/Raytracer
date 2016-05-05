/*
** obj_calculs.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Sun Mar 13 20:30:25 2016 victor sousa
** Last update Thu May  5 07:46:17 2016 Victor Sousa
*/

#include		"main.h"

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
  int			h = hash & 15;
  double u = h < 8 || h == 12 || h == 13 ? x : y;
  double v = h < 4 || h == 12 || h == 13 ? y : z;
  return (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}

double noise(double x, double y, double z)
{
  int p[512] = {151,160,137,91,90,15,
      131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
      190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
      88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
      77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
      102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
      135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
      5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
      223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
      129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
      251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
      49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
      138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
      151,160,137,91,90,15, 131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
      142,8,99,37,240,21,10,23, 190, 6,148,247,120,234,75,0,26,197,62,94,252,219,
      203,117,35,11,32,57,177,33, 88,237,149,56,87,174,20,125,136,171,168, 68,175,
      74,165,71,134,139,48,27,166, 77,146,158,231,83,111,229,122,60,211,133,230,
      220,105,92,41,55,46,245,40,244,102,143,54, 65,25,63,161, 1,216,80,73,209,76,
      132,187,208, 89,18,169,200,196, 135,130,116,188,159,86,164,100,109,198,173,
      186, 3,64,52,217,226,250,124,123, 5,202,38,147,118,126,255,82,85,212,207,206,
      59,227,47,16,58,17,182,189,28,42, 223,183,170,213,119,248,152, 2,44,154,163,
      70,221,153,101,155,167, 43,172,9, 129,22,39,253, 19,98,108,110,79,113,224,
      232,178,185, 112,104,218,246,97,228, 251,34,242,193,238,210,144,12,191,179,
      162,241, 81,51,145,235,249,14,239,107,49,192,214, 31,181,199,106,157,184,
      84,204,176,115,121,50,45,127, 4,150,254,138,236,205,93,222,114,67,29,24,72,
      243,141,128,195,78,66,215,61,156,180};

  int X = (int)floor(x) & 255;
  int Y = (int)floor(y) & 255;
  int Z = (int)floor(z) & 255;
  x -= floor(x);
  y -= floor(y);
  z -= floor(z);
  double u = fade(x);
  double v = fade(y);
  double w = fade(z);
  int A = p[X] + Y;
  int AA = p[A] + Z;
  int AB = p[A + 1] + Z;
  int B = p[X + 1] + Y;
  int BA = p[B] + Z;
  int BB = p[B + 1] + Z;
  return (lerp(w, lerp(v, lerp(u, grad(p[AA], x  , y  , z   ),
			       grad(p[BA], x-1, y  , z   )),
		       lerp(u, grad(p[AB], x  , y-1, z   ),
			    grad(p[BB], x-1, y-1, z   ))),
	       lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),
			    grad(p[BA+1], x-1, y  , z-1 )),
		    lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
			 grad(p[BB+1], x-1, y-1, z-1 )))));
}

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

  float noiseCoefx = noise(0.1 * rcast->new_point.x, 0.1 * rcast->new_point.y, 0.1 * rcast->new_point.z);
  float noiseCoefy = noise(0.1 * rcast->new_point.y, 0.1 * rcast->new_point.z, 0.1 * rcast->new_point.x);
  float noiseCoefz = noise(0.1 * rcast->new_point.z, 0.1 * rcast->new_point.x, 0.1 * rcast->new_point.y);
  rcast->normale.x = (1.0f - rcast->mat_touch->bump) * rcast->normale.x + rcast->mat_touch->bump * noiseCoefx;
  rcast->normale.y = (1.0f - rcast->mat_touch->bump) * rcast->normale.y + rcast->mat_touch->bump * noiseCoefy;
  rcast->normale.z = (1.0f - rcast->mat_touch->bump) * rcast->normale.z + rcast->mat_touch->bump * noiseCoefz;
  float temp = mult_vector(rcast->normale, rcast->normale);
  if (temp == 0.0)
    return (-1);
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

  ve.x = 1;
  ve.y = 0;
  ve.z = 0;
  ve = normalize(ve);

  vp = minus_vector(rcast->new_point, rcast->sphere->center);
  vp = normalize(vp);
  if (!my_strstr(rcast->mat_touch->texture_path, "NULL"))
    {

      phi = acos(-mult_vector(vn,vp));
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
      rcast->mat_touch->color = rcast->mat_touch->texture->color[(int)v][(int)u];
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
