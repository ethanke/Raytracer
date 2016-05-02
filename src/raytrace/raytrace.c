/*
** raytrace.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 01:01:17 2016 victor sousa
** Last update Sun May  1 23:58:41 2016 Victor Sousa
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

t_color			raytrace_loop(t_prog *prog, t_ray *ray, t_bunny_position pos, int depth)
{
  t_raycast		rcast;
  t_ray			new_ray;
  t_color		new_col;
  t_color		out_col;
  int			i_cmp;
  t_light_list		*light_list;
  float			tmp;

  out_col.full = 0xFF000000;
  rcast.hit_dist = 20000;
  if (depth > MAX_DEPTH)
    return (out_col);
  if ((rcast.obj_touch = hit(prog->obj_list, ray, &rcast.hit_dist, &rcast)) != NULL &&
      rcast.obj_touch->obj != NULL)
    {
      if (calc_normale(prog, &rcast, ray, &out_col) == -1)
	return (out_col);
      if (rcast.mat_touch->transpa == 0 && rcast.mat_touch->reflect == 0)
	{
	  light_list = prog->light_list;
	  while (light_list != NULL)
	    {

	      light_list = light_list->next;
	    }
	  /*  Vec3f lightDir, light
	      Intensity;
	      IsectInfo isectShad;
	      lights[i]->illuminate(hitPoint, lightDir, lightIntensity, isectShad.tNear);
	      bool vis = !trace(hitPoint + hitNormal * options.bias, -lightDir, objects, isectShad, kShadowRay);
	      float angle = deg2rad(45);
	      float s = hitTexCoordinates.x * cos(angle) - hitTexCoordinates.y * sin(angle);
	      float t = hitTexCoordinates.y * cos(angle) + hitTexCoordinates.x * sin(angle);
	      float scaleS = 20, scaleT = 20;
	      float pattern = (cos(hitTexCoordinates.y * 2 * M_PI * scaleT) * sin(hitTexCoordinates.x * 2 * M_PI * scaleS) + 1) * 0.5; // isect.hitObject->albedo
		  float pattern = (modulo(s * scaleS) < 0.5) ^ (modulo(t * scaleT) < 0.5);
	  float pattern = (modulo(s * scaleS) < 0.5);
	  hitColor += vis * pattern * lightIntensity * std::max(0.f, hitNormal.dotProduct(-lightDir));*/
	    }
      else if (rcast.mat_touch->transpa == 0 && rcast.mat_touch->reflect > 0)
	{
	  new_ray.start = rcast.hit_point;
	  new_ray.dir = ray->dir;
	}
      else if (rcast.mat_touch->transpa > 0 && rcast.mat_touch->reflect > 0)
	{
	  new_ray.dir = ray->dir;
	  new_ray.start = rcast.hit_point;
	  new_col= raytrace_loop(prog, &new_ray, pos, 0);
	  i_cmp = -1;
	  while (++i_cmp < 3)
	    {
	      out_col.argb[i_cmp] =
	      (new_col.argb[i_cmp] * (1 - (rcast.mat_touch->transpa / 100))) / 2 +
	      (out_col.argb[i_cmp] * (rcast.mat_touch->transpa / 100)) / 2;
	    }
	  /*float kr;
	  fresnel(dir, hitNormal, isect.hitObject->ior, kr);
	  bool outside = dir.dotProduct(hitNormal) < 0;
	  Vec3f bias = options.bias * hitNormal;
	  if (kr < 1)
	    {
	      Vec3f refractionDirection = refract(dir, hitNormal, isect.hitObject->ior).normalize();
	      Vec3f refractionRayOrig = outside ? hitPoint - bias : hitPoint + bias;
	      refractionColor = castRay(refractionRayOrig, refractionDirection, objects, lights, options, depth + 1);
	    }
	  Vec3f reflectionDirection = reflect(dir, hitNormal).normalize();
	  Vec3f reflectionRayOrig = outside ? hitPoint + bias : hitPoint - bias;
	  reflectionColor = castRay(reflectionRayOrig, reflectionDirection, objects, lights, options, depth + 1);

	  hitColor += reflectionColor * kr + refractionColor * (1 - kr);*/
	}
    }
  else
    {
      out_col = prog->background->color[pos.y][pos.x];
    }
  return (out_col);
}

int			raytrace(t_prog *prog)
{
  t_ray			ray;
  t_bunny_position	pos;
  t_color		pix;

  my_putstr("\nRaytracing started\n");
  pos.y = -1;
  while (++pos.y < prog->win_size.y)
    {
      pos.x = -1;
      while (++pos.x < prog->win_size.x)
	{
	  init_ray(&prog->win_size, &ray, &pos, prog);
	  pix = raytrace_loop(prog, &ray, pos, 0);
	  tekpixel(prog->pix, &pos, &pix);
	}
    }
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
  bunny_display(prog->win);
  my_putstr("Raytracing successfull\n");
  return (0);
}
