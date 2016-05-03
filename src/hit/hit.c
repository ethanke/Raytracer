/*
** hit.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Mar  8 23:01:14 2016 victor sousa
** Last update Tue May  3 09:45:09 2016 Victor Sousa
*/

#include	"main.h"

t_obj_list	*hit(t_obj_list *obj_list, t_ray *ray, float *dist, t_raycast *rcast)
{
  t_obj_list	*out;
  t_obj_list	*tmp;
  t_circle	base;
  t_cone	*cone;

  if ((out = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  out->obj = NULL;
  tmp = obj_list;
  while (tmp != NULL)
    {
      if (tmp->type == 's' &&
	  hit_sphere(ray, (t_sphere *)tmp->obj, dist))
	{
	  out->type = tmp->type;
	  out->obj = tmp->obj;
      	}
      if (tmp->type == 't' &&
	  hit_triangle(ray, (t_triangle *)tmp->obj, dist))
  	{
  	  out->type = tmp->type;
  	  out->obj = tmp->obj;
  	}
      if (tmp->type == 'p' &&
    	  hit_plan(ray, (t_plan *)tmp->obj, dist))
    	{
    	  out->type = tmp->type;
    	  out->obj = tmp->obj;
    	}
      if (tmp->type == 'y' &&
	  hit_cylin(ray, (t_cylin *)tmp->obj, dist, rcast))
      	{
      	  out->type = tmp->type;
      	  out->obj = tmp->obj;
      	}
      if (tmp->type == 'i' &&
	  hit_circle(ray, (t_circle *)tmp->obj, dist, rcast))
	{
	  out->type = tmp->type;
	  out->obj = tmp->obj;
	}
      if (tmp->type == 'c' &&
	  hit_cone(ray, (t_cone *)tmp->obj, dist))
  	{
	  cone = (t_cone *)tmp->obj;
	  base.plan.center.x = cone->center.x;
	  base.plan.center.y = cone->center.y;
	  base.plan.center.z = cone->center.z;
	  base.plan.dir.x = cone->dir.x;
	  base.plan.dir.y = cone->dir.y;
	  base.plan.dir.z = cone->dir.z;
	  base.radius = cone->radius;
	  hit_circle(ray, &base, dist, rcast);
  	  out->type = tmp->type;
  	  out->obj = tmp->obj;
  	}
      tmp = tmp->next;
    }
  out->next = NULL;
  return (out);
}
