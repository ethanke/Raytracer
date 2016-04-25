/*
** load_mat.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Thu Mar 10 23:59:29 2016 victor sousa
** Last update Fri Mar 11 00:33:36 2016 victor sousa
*/

#include		"main.h"

int                     load_mat(t_prog *prog, char **file)
{
  int                   i;
  int                   mat_count;
  char                  *get;

  if ((get = get_field(file, "scene:material_list:count")) == NULL)
    return (-1);
  mat_count = my_getnbr(get);
  free(get);
  prog->mat_list = NULL;

  i = 0;
  while (i < mat_count)
    {
      if ((prog->mat_list = add_mat(prog->mat_list, file, i)) == NULL)
        return (-1);
      i++;
    }
  return (0);
}
