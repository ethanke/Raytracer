/*
** hit.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Mar  8 23:01:14 2016 victor sousa
** Last update Fri Apr 29 18:11:32 2016 Victor Sousa
*/

#include	"main.h"

t_obj_list	*hit(t_obj_list *obj_list, t_ray *ray, float *dist, t_raycast *rcast)
{
  t_obj_list	*out;
  t_circle	base;
  t_cone	*cone;

  if ((out = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  out->obj = NULL;
  while (obj_list != NULL)
    {
      if (obj_list->type == 's' &&
	  hit_sphere(ray, (t_sphere *)obj_list->obj, dist))
	{
	  out->type = obj_list->type;
	  out->obj = obj_list->obj;
      	}
      if (obj_list->type == 't' &&
	  hit_triangle(ray, (t_triangle *)obj_list->obj, dist))
  	{
  	  out->type = obj_list->type;
  	  out->obj = obj_list->obj;
  	}
        if (obj_list->type == 'p' &&
  	  hit_plan(ray, (t_plan *)obj_list->obj, dist))
  	{
  	  out->type = obj_list->type;
  	  out->obj = obj_list->obj;
  	}
      if (obj_list->type == 'c' &&
	  hit_cone(ray, (t_cone *)obj_list->obj, dist))
  	{
	  cone = (t_cone *)obj_list->obj;
	  base.plan.center.x = cone->center.x;
	  base.plan.center.y = cone->center.y;
	  base.plan.center.z = cone->center.z;
	  base.plan.dir.x = cone->dir.x;
	  base.plan.dir.y = cone->dir.y;
	  base.plan.dir.z = cone->dir.z;
	  base.radius = cone->radius;
	  hit_circle(ray, &base, dist, rcast);
  	  out->type = obj_list->type;
  	  out->obj = obj_list->obj;
  	}
      obj_list = obj_list->next;
    }
  out->next = NULL;
  return (out);
}
