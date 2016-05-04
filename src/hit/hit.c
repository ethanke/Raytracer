/*
** hit.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Mar  8 23:01:14 2016 victor sousa
** Last update Wed May  4 21:37:29 2016 Victor Sousa
*/

#include	"main.h"

t_obj_list	*hit(t_obj_list *obj_list, t_ray *ray, float *dist)
{
  t_obj_list	*out;
  t_obj_list	*tmp;
  t_cylin	*cylin;

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
      if (tmp->type == 'y')
      	{
	  cylin = tmp->obj;
	 if (hit_cylin(ray, cylin, dist))
	    {
	      out->type = tmp->type;
      	      out->obj = tmp->obj;
	    }
	  /*if (hit_circle(ray, cylin->cap[0], dist))
	    {
	      out->type = 'i';
      	      out->obj = cylin->cap[0];
	    }*/
	 if (hit_circle(ray, cylin->cap[1], dist))
	    {
	      out->type = 'i';
	      out->obj = cylin->cap[1];
	    }
	}
      if (tmp->type == 'i' &&
	  hit_circle(ray, (t_circle *)tmp->obj, dist))
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
