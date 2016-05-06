/*
** hit.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Mar  8 23:01:14 2016 victor sousa
** Last update Thu May  5 11:56:33 2016 Victor Sousa
*/

#include	"main.h"

t_obj_list	*hit(t_obj_list *obj_list, t_ray *ray, float *dist)
{
  t_obj_list	*out;
  t_obj_list	*tmp;
  t_cylin	*cy;
  t_cone	*co;
  t_pill	*pi;

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
      if (tmp->type == 'p' &&
	  hit_circle(ray, (t_circle *)tmp->obj, dist))
	{
	  out->type = tmp->type;
	  out->obj = tmp->obj;
	}
      if (tmp->type == 'u' &&
	  hit_cube(ray, (t_cube *)tmp->obj, dist))
	{
	  out->type = tmp->type;
	  out->obj = tmp->obj;
	}
      if (tmp->type == 'y')
      	{
	  cy = tmp->obj;
	  if (hit_cylin(ray, cy, dist))
      	    {
      	      out->type = tmp->type;
      	      out->obj = cy;
	    }
	  if (hit_circle(ray, cy->cap[0], dist))
	    {
	      out->type = 'i';
	      out->obj = cy->cap[0];
	    }
	  if (hit_circle(ray, cy->cap[1], dist))
	    {
	      out->type = 'i';
	      out->obj = cy->cap[1];
	    }
	}
      if (tmp->type == 'l')
	{
	  pi = tmp->obj;
	  if (hit_cylin(ray, pi->cylin, dist))
	    {
	      out->type = 'y';
	      out->obj = pi->cylin;
	    }
	  if (hit_sphere(ray, pi->cap[0], dist))
	    {
	      out->type = 's';
	      out->obj = pi->cap[0];
	    }
	  if (hit_sphere(ray, pi->cap[1], dist))
	    {
	      out->type = 's';
	      out->obj = pi->cap[1];
	    }
  	}
      if (tmp->type == 'c')
  	{
	  co = tmp->obj;
	  if (hit_cone(ray, co, dist))
	    {
	      out->type = tmp->type;
	      out->obj = tmp->obj;
	    }
	  if (hit_circle(ray, co->cap, dist))
	    {
	      out->type = 'i';
	      out->obj = cy->cap;
	    }
  	}
      tmp = tmp->next;
    }
  out->next = NULL;
  return (out);
}
