/*
** load_forme.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/loading/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Mon Apr 25 23:38:14 2016 Gaëtan Léandre
** Last update Wed Apr 27 16:36:05 2016 Victor Sousa
*/

#include		"main.h"

int			where_are_formes(char **file)
{
  int			i;

  i = 0;
  while (file[i] && file[i][0] != 'f')
    i++;
  return (i);
}

int			get_sommet_size(char *str)
{
  int			i;
  int			j;

  i = 0;
  j = 0;
  while (str[i])
    {
      if (str[i] != ' ' && (i - 1 < 0 || str[i - 1] == ' '))
	j++;
      i++;
    }
  return (j - 1);
}

t_obj_list		*create_triangle(char *str, t_obj_list *prev, t_vtx_list *list)
{
  t_obj_list            *new;
  t_triangle            *t;
  int			i;
  int			j;
  int			pos;

  if ((new = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((t = malloc(sizeof(t_triangle))) == NULL)
    return (NULL);
  i = (j = 0) * 0;
  pos = 0;
  while (i < 3)
    {
      while (str[pos] != ' ')
	pos++;
      t->angle[i] = get_vertex_in_list(list, my_getnbr(&str[++pos]), &j);
      i++;
      if (j == -1)
	return (NULL);
    }
  t->material = 1;
  new->obj = t;
  new->type = 't';
  new->next = prev;
  return (new);
}

t_obj_list		*create_square(char *str, t_obj_list *prev, t_vtx_list *list)
{
  t_obj_list            *new;
  t_triangle            *t;
  int			i;
  int			j;
  int			pos;

  if ((new = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((t = malloc(sizeof(t_square))) == NULL)
    return (NULL);
  i = (j = 0) * 0;
  pos = 0;
  while (i < 4)
    {
      while (str[pos] != ' ')
	pos++;
      t->angle[i++] = get_vertex_in_list(list, my_getnbr(&str[++pos]), &j);
      if (j == -1)
	return (NULL);
    }
  t->material = 1;
  new->obj = t;
  new->type = 'q';
  new->next = prev;
  return (new);
}

t_obj_list		*associate_obj(char *str, t_obj_list *prev, t_vtx_list *list)
{
  int			size;

  size = get_sommet_size(str);
  if (size == 3)
    return(create_triangle(str, prev, list));
  else if (size == 4)
    return(create_square(str, prev, list));
  return (NULL);
}

t_obj_list		*parse_obj_formes(char **file, t_vtx_list *list)
{
  int			i;
  t_obj_list		*prev;

  prev = NULL;
  i = where_are_formes(file);
  while (file[i])
    {
      if (file[i][0] == 'f')
	{
	  prev = associate_obj(file[i], prev, list);
	  if (prev == NULL)
	    return (NULL);
	}
      i++;
    }
  printf("i face : %d\n", i);
  return (prev);
}
