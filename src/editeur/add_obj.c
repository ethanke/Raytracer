/*
** add_obj.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Mon May  2 17:19:25 2016 Ethan Kerdelhue
** Last update Tue May  3 01:03:26 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			push_cone(t_prog *prog, t_cone con)
{
  t_obj_list		*tmp;
  t_obj_list		*new_obj;
  t_cone		*new;

  if ((new = malloc(sizeof(t_cone))) == NULL)
    return (-1);
  if ((new_obj = malloc(sizeof(t_obj_list))) == NULL)
    return (-1);
  new->center = con.center;
  new->dir = con.dir;
  new->radius = con.radius;
  new->height = con.height;
  new->material = con.material;
  tmp = prog->obj_list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  new_obj->type = 'c';
  new_obj->obj = (void *) new;
  new_obj->next = NULL;
  tmp->next = new_obj;
  return (0);
}

int			push_plan(t_prog *prog, t_plan pla)
{
  t_obj_list		*tmp;
  t_obj_list		*new_obj;
  t_plan		*new;

  if ((new = malloc(sizeof(t_plan))) == NULL)
    return (-1);
  if ((new_obj = malloc(sizeof(t_obj_list))) == NULL)
    return (-1);
  new->center = pla.center;
  new->dir = pla.dir;
  new->material = pla.material;
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

t_coord			*get_coord(t_coord *tmp)
{
  char			*str;

  my_printf(1, "x :\n");
  if ((str = get_next_line(0)) == NULL)
    return (NULL);
  tmp->x = my_atof(str);
  free(str);
  my_printf(1, "y :\n");
  if ((str = get_next_line(0)) == NULL)
    return (NULL);
  tmp->y = my_atof(str);
  free(str);
  my_printf(1, "z :\n");
  if ((str = get_next_line(0)) == NULL)
    return (NULL);
  tmp->z = my_atof(str);
  free(str);
  return (tmp);
}

char			get_material(t_prog *prog)
{
  char			*str;
  int			flag;
  int			val;

  flag = 0;
  while (flag != 1)
    {
      my_printf(1, "material id :\n");
      if ((str = get_next_line(0)) == NULL)
	return (-1);
      val = (char) my_getnbr(str);
      if (check_material_id(prog, (char) val) == 1)
	flag = 1;
      else
	my_printf(1, "material_id %d do not exist !\n", (int) val);
    }
  return (val);
}

int			add_obj_triangle(t_prog *prog)
{
  t_triangle 		tmp;

  my_printf(1, "Coordonée du premier point du triangle\n");
  if ((get_coord(&tmp.angle[0])) == NULL)
    return (-1);
  my_printf(1, "Coordonée du deuxième point du triangle\n");
  if ((get_coord(&tmp.angle[1])) == NULL)
    return (-1);
  my_printf(1, "Coordonée du troisième point du triangle\n");
  if ((get_coord(&tmp.angle[2])) == NULL)
    return (-1);
  push_triangle(prog, tmp);
  return (0);
}

int			add_obj_sphere(t_prog *prog)
{
  t_sphere		tmp;
  char			*str;

  my_printf(1, "Coordonée du point central :\n");
  get_coord(&tmp.center);
  my_printf(1, "rayon :\n");
  str = get_next_line(0);
  tmp.radius = my_getnbr(str);
  free(str);
  tmp.material = get_material(prog);
  if ((push_sphere(prog, tmp)) == -1)
    return (-1);
  return (0);
}

int			add_obj_plan(t_prog *prog)
{
  t_plan		plan;

  my_printf(1, "Entrez les coordonées centre du plan :\n");
  get_coord(&plan.center);
  my_printf(1, "Entrez les coordonées de direction du plan :\n");
  get_coord(&plan.dir);
  if ((plan.material = get_material(prog)) == -1)
    return (-1);
  push_plan(prog, plan);
  return (0);
}

int			add_obj_cone(t_prog *prog)
{
  t_cone		cone;
  char			*str;

  my_printf(1, "Entrez les coordonées centre du cone :\n");
  get_coord(&cone.center);
  my_printf(1, "Entrez les coordonées de direction du cone :\n");
  get_coord(&cone.dir);
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  cone.radius = my_getnbr(str);
  free(str);
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  cone.height = my_getnbr(str);
  free(str);
  if ((cone.material = get_material(prog)) == -1)
    return (-1);
  push_cone(prog, cone);
  return (0);
}

int			add_obj(t_prog *prog)
{
  char			*str;

  if (prog->editor->fd == -1)
    return (put_error(ERR_NOFD));
  my_printf(1, "Quelle objet voulez-vous rajoutez ?\n");
  my_printf(1, "\n 1 - Sphere\n 2 - Triangle\n 3 - Plan\n");
  str = get_next_line(0);
  if (my_strcmp(str, "1") == 0)
    add_obj_sphere(prog);
  else if (my_strcmp(str, "2") == 0)
    add_obj_triangle(prog);
  else if (my_strcmp(str, "3") == 0)
    add_obj_plan(prog);
  else if (my_strcmp(str, "3") == 0)
    add_obj_cone(prog);
  else
    my_printf(1, "Error : Your choice has no result\n");
  return (0);
}
