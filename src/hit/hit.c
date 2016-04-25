/*
** hit.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Tue Mar  8 23:01:14 2016 victor sousa
** Last update Fri Mar 11 02:27:26 2016 victor sousa
*/

#include	"main.h"

t_obj_list	*hit(t_obj_list *obj_list, t_ray *ray, float *dist)
{
  t_obj_list	*out;

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
      obj_list = obj_list->next;
    }
  out->next = NULL;
  return (out);
}
