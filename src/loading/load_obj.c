/*
** load_sphere.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Thu Mar 10 23:26:06 2016 victor sousa
** Last update Tue May  3 23:51:44 2016 Victor Sousa
*/

#include		"main.h"

int			while_load_obj(char **file, char *get,
				       char *type_lf, t_prog *prog)
{
  int			i;
  int			obj_count;

  obj_count = my_getnbr(get);
  free(get);
  i = -1;
  while (++i < obj_count)
    {
      type_lf[21] = i + 49;
      if ((get = get_field(file, type_lf)) == NULL)
	{
	  my_printf(1, "Could not find scene:object_list:obj%d:type\n", i + 1);
	  return (-1);
	}
      if (my_strstr(get, "sphere"))
	{
	  if ((prog->obj_list = add_sphere(prog->obj_list, file, i))
	      == NULL)
	    return (-1);
	}
	else if (my_strstr(get, "triangle"))
	{
	  if ((prog->obj_list = add_triangle(prog->obj_list, file, i))
	      == NULL)
	    return (-1);
	}
	else if (my_strstr(get, "plan"))
  	{
  	  if ((prog->obj_list = add_plan(prog->obj_list, file, i))
  	      == NULL)
  	    return (-1);
  	}
      else if (my_strstr(get, "cone"))
	{
    	  if ((prog->obj_list = add_cone(prog->obj_list, file, i))
    	      == NULL)
    	    return (-1);
    	}
      else if (my_strstr(get, "cylinder"))
	{
	  if ((prog->obj_list = add_cyl(prog->obj_list, file, i))
	      == NULL)
	    return (-1);
	}
      else
	return (-1);
      free(get);
    }
  my_putchar('\n');
  return (0);
}

int                     load_obj(t_prog *prog, char **file)
{
  char                  *type_lf;
  char                  *get;

  if ((get = get_field(file, "scene:object_list:count")) == NULL)
    {
      my_printf(1, "Could not find scene:object_list:count\n");
      return (-1);
    }
  prog->obj_list = NULL;
  if ((type_lf = malloc(sizeof(char) *
			my_strlen("scene:object_list:objX:type") + 1)) == NULL)
    return (-1);
  type_lf[0] = '\0';
  type_lf = my_strcat(type_lf, "scene:object_list:objX:type");
  return (while_load_obj(file, get, type_lf, prog));
}
