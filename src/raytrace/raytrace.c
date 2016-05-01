/*
** raytrace.c for raytrace in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 01:01:17 2016 victor sousa
** Last update Sun May  1 14:43:07 2016 Victor Sousa
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

t_color			raytrace_loop(t_prog *prog, t_raycast *rcast, int depth)
{
  t_color		out;

  out.full = 0xFF0F0F0F;
  if (depth > MAX_DEPTH)
    return (out);
  if (hit(prog->obj_list, &rcast->ray, &rcast->dist, rcast))
    {
      /*Vec3f hitPoint = orig + dir * isect.tNear;
      Vec3f hitNormal;
      Vec2f hitTexCoordinates;
      isect.hitObject->getSurfaceProperties(hitPoint, dir, isect.index, isect.uv, hitNormal, hitTexCoordinates);
      switch (isect.hitObject->type)
	{
	  case kDiffuse:
	    {
	      for (uint32_t i = 0; i < lights.size(); ++i)
		{
		  Vec3f lightDir, lightIntensity;
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
		      hitColor += vis * pattern * lightIntensity * std::max(0.f, hitNormal.dotProduct(-lightDir));
		    }
		  break;
		}
	      case kReflection:
		{
		  Vec3f R = reflect(dir, hitNormal);
		  R.normalize();
		  break;
		}
	      case kReflectionAndRefraction:
		{
		  Vec3f refractionColor = 0, reflectionColor = 0;
		  float kr;
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

		  hitColor += reflectionColor * kr + refractionColor * (1 - kr);
		  break;
		}
	      default:
	      break;
      }*/
    }
  else
    {
      out = prog->background->color[rcast->pos.y][rcast->pos.x];
    }
  return (out);
}

int			raytrace(t_prog *prog)
{
  t_raycast		raycast;
  t_color		pix;

  my_putstr("\nRaytracing started\n");
  raycast.touch_circle = 0;
  raycast.pos.y = -1;
  while (++raycast.pos.y < prog->win_size.y)
    {
      raycast.pos.x = -1;
      while (++raycast.pos.x < prog->win_size.x)
	{
	  init_ray(&prog->win_size, &raycast.ray, &raycast.pos, prog);
	  pix = raytrace_loop(prog, &raycast, 0);
	  tekpixel(prog->pix, &raycast.pos, &pix);
	}
    }
  raycast.pos.x = 0;
  raycast.pos.y = 0;
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, &raycast.pos);
  bunny_display(prog->win);
  my_putstr("Raytracing successfull\n");
  return (0);
}
