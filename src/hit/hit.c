/*
** hit.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Mar  8 23:01:14 2016 victor sousa
** Last update Wed May  4 22:34:22 2016 Victor Sousa
*/

#include	"main.h"

t_obj_list	*hit(t_obj_list *obj_list, t_ray *ray, float *dist)
{
  t_obj_list	*out;
  t_obj_list	*tmp;

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
	  hit_cylin(ray, (t_cylin *)tmp->obj, dist))
      	{
	  out->type = tmp->type;
	  out->obj = tmp->obj;
	}
      if (tmp->type == 'c' &&
	  hit_cone(ray, (t_cone *)tmp->obj, dist))
  	{
	  out->type = tmp->type;
  	  out->obj = tmp->obj;
  	}
      tmp = tmp->next;
    }
  out->next = NULL;
  return (out);
}
