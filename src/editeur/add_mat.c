/*
** add_mat.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Wed Apr 27 16:18:56 2016 Ethan Kerdelhue
** Last update Wed Apr 27 18:05:24 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			push_mat(t_prog *prog, t_mat_list mat)
{
  t_mat_list		*tmp;
  t_mat_list		*new;

  tmp = prog->mat_list;
  if ((new = malloc(sizeof(t_mat_list))) == NULL)
    return (-1);
  new->id = count_material(prog) + 1;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
  new->color = mat.color;
  new->reflect = mat.reflect;
  new->next = NULL;
  return (0);
}

t_color			get_rgb(int flag)
{
  t_color		tmp;
  char			*str;
  int			i;

  i = RED_CMP;
  while (flag != 1)
    {
      if (i == RED_CMP)
	my_printf(0, "Rouge :\n");
      if (i == GREEN_CMP)
	my_printf(0, "Vert :\n");
      if (i == BLUE_CMP)
	my_printf(0, "Bleu :\n");
      str = get_next_line(0);
      if (my_getnbr(str) >= 0 || my_getnbr(str) <= 255)
	{
	  tmp.argb[i] = my_getnbr(str);
	  if (i == BLUE_CMP)
	    flag = 1;
	  i++;
	}
      else
	my_printf(0, "Error : valeur uniquement entre 0 et 255");
      free(str);
    }
  return (tmp);
}

int			add_mat_s(t_prog *prog)
{
  t_mat_list		tmp;
  char 			*str;

  my_printf(0, "Entrez les couleurs RGB :\n");
  tmp.color = get_rgb(0);
  my_printf(0, "Reflection :\n");
  str = get_next_line(0);
  tmp.reflect = my_getnbr(str);
  free(str);
  push_mat(prog, tmp);
  return (0);
}
