/*
** add_obj.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Wed Apr 27 14:14:15 2016 Ethan Kerdelhue
** Last update Sun May  1 08:49:41 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			push_plan(t_prog *prog, t_plan pla)
{
  t_obj_list		*tmp;
  t_obj_list		*new_obj;
  t_plan		*new;

  if ((new = malloc(sizeof(t_plan))) == NULL)
    return (-1);
  if ((new_obj = malloc(sizeof(t_obj_list))) == NULL)
    return (-1);
  new->center = &plan.center;
  new->dir = &plan.dir;
  new->material = sph.material;
  tmp = prog->obj_list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  new_obj->type = 'p';
  new_obj->obj = (void *) new;
  new_obj->next = NULL;
  tmp->next = new_obj;
  return (0);
}

int			push_sphere(t_prog *prog, t_sphere sph)
{
  t_obj_list		*tmp;
  t_obj_list		*new_obj;
  t_sphere		*new;

  if ((new = malloc(sizeof(t_sphere))) == NULL)
    return (-1);
  if ((new_obj = malloc(sizeof(t_obj_list))) == NULL)
    return (-1);
  new->center.x = sph.center.x;
  new->center.y = sph.center.y;
  new->center.z = sph.center.z;
  new->radius = sph.radius;
  new->material = sph.material;
  tmp = prog->obj_list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  new_obj->type = 's';
  new_obj->obj = (void *) new;
  new_obj->next = NULL;
  tmp->next = new_obj;
  return (0);
}

int			check_material_id(t_prog *prog, char m_id)
{
  t_mat_list		*tmp;

  tmp = prog->mat_list;
  while (tmp != NULL)
    {
      if ((int) m_id == tmp->id)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

int			push_triangle(t_prog *prog, t_triangle tri)
{
  t_obj_list		*tmp;
  t_obj_list		*new_obj;
  t_triangle		*new;

  if ((new = malloc(sizeof(t_triangle))) == NULL)
    return (-1);
  if ((new_obj = malloc(sizeof(t_obj_list))) == NULL)
    return (-1);
  tmp = prog->obj_list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  new->angle[0] = tri.angle[0];
  new->angle[1] = tri.angle[1];
  new->angle[2] = tri.angle[2];
  new->material = tri.material;
  new_obj->type = 't';
  new_obj->obj = (void *) new;
  new_obj->next = NULL;
  tmp->next = new_obj;
  return (0);
}

t_coord			*get_coord()
{
  t_coord		*tmp;
  char			*str;

  if ((tmp = malloc(sizeof(t_coord))) == NULL)
    return (NULL);
  my_printf(0, "x :\n");
  if ((str = get_next_line(0)) == NULL)
    return (NULL);
  tmp->x = my_atof(str);
  free(str);
  my_printf(0, "y :\n");
  if ((str = get_next_line(0)) == NULL)
    return (NULL);
  tmp->y = my_atof(str);
  free(str);
  my_printf(0, "z :\n");
  if ((str = get_next_line(0)) == NULL)
    return (NULL);
  tmp->z = my_atof(str);
  free(str);
  return (tmp);
}

int			add_obj_triangle(t_prog *prog)
{
  t_triangle 		tmp;
  char			*str;
  int			flag;

  flag = 0;
  my_printf(0, "Coordonée du premier point du triangle\n");
  if ((tmp.angle[0] = *get_coord()) == NULL)
    return (-1);
  my_printf(0, "Coordonée du deuxième point du triangle\nx:\n");
  if ((tmp.angle[1] = get_coord()) == NULL)
    return (-1);
  my_printf(0, "Coordonée du troisième point du triangle\nx:\n");
  if ((tmp.angle[2] = get_coord()) == NULL)
    return (-1);
  while (flag != 1)
    {
      my_printf(0, "material id :\n");
      if ((str = get_next_line(0)) == NULL)
	return (-1);
      tmp.material = (char) my_getnbr(str);
      if (check_material_id(prog, tmp.material) == 1)
	flag = 1;
      else
	my_printf(0, "material_id %d do not exist !\n", (int) tmp.material);
    }
  push_triangle(prog, tmp);
  return (0);
}

int			add_obj_sphere(t_prog *prog)
{
  t_sphere		tmp;
  char			*str;
  int			flag;

  flag = 0;
  my_printf(0, "Coordonée du point central :\n");
  tmp.center = *(get_coord(prog));
  my_printf(0, "rayon :\n");
  str = get_next_line(0);
  tmp.radius = my_getnbr(str);
  free(str);
  while (flag != 1)
    {
      my_printf(0, "material id :\n");
      if ((str = get_next_line(0)) == NULL)
	return (-1);
      tmp.material = (char) my_getnbr(str);
      if (check_material_id(prog, tmp.material) == 1)
	flag = 1;
      else
	my_printf(0, "material_id %d do not exist !\n", (int) tmp.material);
    }
  if ((push_sphere(prog, tmp)) == -1)
    return (-1);
  return (0);
}

int			add_obj_plan(t_prog *prog)
{
  t_plan		plan;
  (void) prog;
  return (0);
}

int			add_obj(t_prog *prog)
{
  char			*str;

  if (prog->editor->fd == -1)
    return (put_error(ERR_NOFD));
  my_printf(0, "Quelle objet voulez-vous rajoutez ?\n 1 - Sphere\n 2 - Triangle\n 3 - Plan\n");
  str = get_next_line(0);
  if (my_strcmp(str, "1") == 0)
    add_obj_sphere(prog);
  else if (my_strcmp(str, "2") == 0)
    add_obj_triangle(prog);
  else if (my_strcmp(str, "3") == 0)
    add_obj_plan(prog);
  else
    my_printf(0, "Error : Your choice has no result\n");
  return (0);
}
