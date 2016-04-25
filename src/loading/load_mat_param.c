/*
** load_material.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Thu Mar 10 23:55:20 2016 victor sousa
** Last update Fri Mar 11 00:09:04 2016 victor sousa
*/

#include	"main.h"

int			get_mat_red(t_mat_list *new, char **file, int id)
{
  char			*lf;
  char			*get;

 if ((lf = malloc(sizeof(char) *
		  my_strlen("scene:material_list:matX:red") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:material_list:matX:red");
  lf[23] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  new->color.argb[RED_CMP] = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

int			get_mat_green(t_mat_list *new, char **file, int id)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:material_list:matX:green") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:material_list:matX:green");
  lf[23] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  new->color.argb[GREEN_CMP] = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

int			get_mat_blue(t_mat_list *new, char **file, int id)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:material_list:matX:blue") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:material_list:matX:blue");
  lf[23] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  new->color.argb[BLUE_CMP] = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

int			get_mat_reflect(t_mat_list *new, char **file, int id)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:material_list:matX:reflect") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:material_list:matX:reflect");
  lf[23] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  new->reflect = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

t_mat_list              *add_mat(t_mat_list *prev, char **file, int id)
{
  t_mat_list            *new;

  if ((new = malloc(sizeof(t_mat_list))) == NULL)
    return (NULL);
  if (get_mat_red(new, file, id) != 0)
    return (NULL);
  if (get_mat_green(new, file, id) != 0)
    return (NULL);
  if (get_mat_blue(new, file, id) != 0)
    return (NULL);
  if (get_mat_reflect(new, file, id) != 0)
    return (NULL);
  new->id = id + 1;
  new->next = prev;
  return (new);
}
