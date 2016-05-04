/*
** edit_cam.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Fri Apr 29 22:08:18 2016 Ethan Kerdelhue
** Last update Wed May  4 17:29:16 2016 Ethan Kerdelhue
*/

#include		"main.h"


int			edit_win_size_x(t_prog *prog)
{
  char			*str;
  int			flag;
  int			val;

  val = 0;
  flag = 0;
  my_printf(1, "Width size (x)\n");
  while (flag != 1)
    {
      if ((str = get_next_line(0)) == NULL)
	return (-1);
      val = my_getnbr(str);
      if ((val >= 1 && val <= 1980) || str[0] == '\0')
	{
	  if (str[0] == '\0')
	    prog->win_size.x = prog->win_size.x;
	  else
	    prog->win_size.x = val;
	  flag = 1;
        }
      else
	my_printf(1, "Error : la valeur doit être comprise entre 1 et 1980\n");
      free(str);
    }
  return (0);
}

int			edit_win_size_y(t_prog *prog)
{
  char			*str;
  int			flag;
  int			val;

  val = 0;
  flag = 0;
  my_printf(1, "Height size (y)\n");
  while (flag != 1)
    {
      if ((str = get_next_line(0)) == NULL)
	return (-1);
      val = my_getnbr(str);
      if ((val >= 1 && val <= 1080) || str[0] == '\0')
	{
	  if (str[0] == '\0')
	    prog->win_size.y = prog->win_size.y;
	  else
	    prog->win_size.y = val;
	  flag = 1;
        }
      else
	my_printf(1, "Error : la valeur doit être comprise entre 1 et 1080\n");
      free(str);
    }
  return (0);
}

int			edit_win(t_prog *prog)
{
  if ((edit_win_size_x(prog)) == -1)
    return (-1);
  if ((edit_win_size_y(prog)) == -1)
    return (-1);
  return (0);
}

int			edit_point(t_point *tmp)
{
  char			*str;

  my_printf(1, "x :\n");
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  tmp->x = ((str[0] != '\0') ? (my_getnbr(str)) : (tmp->x));
  free(str);
  my_printf(1, "y :\n");
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  tmp->y = ((str[0] != '\0') ? (my_getnbr(str)) : (tmp->y));
  free(str);
  my_printf(1, "z :\n");
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  tmp->z = ((str[0] != '\0') ? (my_getnbr(str)) : (tmp->z));
  return (0);
}

int			edit_cam_pos(t_prog *prog)
{
  my_printf(1, "Position de la caméra\n");
  if ((edit_point(&prog->cam_pos)) == -1)
    return (-1);
  my_printf(1, "Regard de la caméra\n");
  if ((edit_point(&prog->cam_pos)) == -1)
    return (-1);
  return (0);
}

int			edit_cam(t_prog *prog)
{
  char			*str;

  if (aff_win_prop(0, prog) == -1)
    return (-1);
  my_printf(1, "Laissez vide pour concerver la valeur\n");
  my_printf(1, "Screen size\n");
  if ((edit_win(prog)) == -1)
    return (-1);
  if ((edit_cam_pos(prog)) == -1)
    return (-1);
  my_printf(1, "Champs de vision (field of view)\n");
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  if (str[0] != '\0')
    {
      prog->cam_fov.x = my_getnbr(str);
      prog->cam_fov.y = prog->cam_fov.x *
	  ((prog->win_size.x / prog->win_size.y) / 1.5);
    }
  my_printf(1, "Anti-aliasing :\n");
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  prog->anti_alias = ((str[0] != 0) ? (my_getnbr(str)) : (prog->anti_alias));
  return (0);
}
