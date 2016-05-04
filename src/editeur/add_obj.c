/*
** add_obj.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Mon May  2 17:19:25 2016 Ethan Kerdelhue
** Last update Wed May  4 19:37:09 2016 Ethan Kerdelhue
*/

#include		"main.h"

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

int			add_obj_cylindre(t_prog *prog)
{
  t_cylin		cylindre;
  char			*str;

  my_printf(1, "Entrez les coordonées centre du cylindre :\n");
  get_coord(&cylindre.center);
  my_printf(1, "Entrez les coordonées de direction du cylindre :\n");
  get_coord(&cylindre.dir);
  my_printf(1, "Entrez le rayon:\n");
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  cylindre.radius = my_getnbr(str);
  free(str);
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  cylindre.height = my_getnbr(str);
  free(str);
  if ((cylindre.material = get_material(prog)) == -1)
    return (-1);
  push_cylindre(prog, cylindre);
  return (0);
}

int			add_obj_circle(t_prog *prog)
{
  t_circle		circle;
  char			*str;


  my_printf(1, "Entrez les coordonées du centre du cylindre :\n");
  edit_coord(&circle.plan.center);
  my_printf(1, "Entrez les coordonées de direction du cylindre :\n");
  edit_coord(&circle.plan.dir);
  my_printf(1, "Entrez le rayon:\n");
  if ((str = get_next_line(0)) == NULL)
    return (-1);
  circle.radius = my_getnbr(str);
  free(str);
  if ((circle.material = get_material(prog)) == -1)
      return (-1);
  push_circle(prog, circle);
  return (0);
}

int			add_obj(t_prog *prog)
{
  char			*str;

  if (prog->editor->fd == -1)
    return (put_error(ERR_NOFD));
  my_printf(1, "Quelle objet voulez-vous rajoutez ?\n\n 1 - Sphere\n");
  my_printf(1, " 2 - Triangle\n 3 - Plan\n 4 - Cone\n 5 - Cylindre\n 6 - Cercle\n");
  str = get_next_line(0);
  if (my_strcmp(str, "1") == 0)
    add_obj_sphere(prog);
  else if (my_strcmp(str, "2") == 0)
    add_obj_triangle(prog);
  else if (my_strcmp(str, "3") == 0)
    add_obj_plan(prog);
  else if (my_strcmp(str, "4") == 0)
    add_obj_cone(prog);
  else if (my_strcmp(str, "5") == 0)
    add_obj_cylindre(prog);
  else if (my_strcmp(str, "6") == 0)
    add_obj_circle(prog);
  else
    my_printf(1, "Error : Your choice has no result\n");
  return (0);
}
