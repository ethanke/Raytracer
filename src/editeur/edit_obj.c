/*
** edit_obj.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Wed Apr 27 18:31:29 2016 Ethan Kerdelhue
** Last update Thu May  5 01:24:19 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			aff_obj_spec(t_prog *prog, int id)
{
  int			i;
  t_obj_list		*tmp;

  i = 0;
  tmp = prog->obj_list;
  while (id != i)
    {
      i++;
      if (tmp->next)
	tmp = tmp->next;
      else
	{
	  my_printf(1, "Error : id %d don't found\n", id);
	  return (-1);
	}
    }
  my_printf(1, "\t<obj%d>\n", (count_object(prog) - id));
  my_printf(1, "\t\t<type>%s</type>\n", get_type(tmp->type));
  aff_obj(0, tmp);
  my_printf(1, "\t</obj%d>\n", (count_object(prog) - id));
  return (0);
}

int			check_obj_id(t_prog *prog, int id)
{
  t_obj_list		*tmp;
  int			i;

  i = 0;
  tmp = prog->obj_list;
  while (tmp != NULL)
    {
      if (i == id)
	return (1);
      i++;
      tmp = tmp->next;
    }
  if (i == id)
    return (1);
  return (0);
}

t_obj_list		*get_obj_ptr(t_prog *prog, int id)
{
  t_obj_list		*tmp;
  int			i;

  i = 0;
  tmp = prog->obj_list;
  while (id != i)
    {
      i++;
      tmp = tmp->next;
    }
  return (tmp);
}

int			edit_coord(t_coord *tmp)
{
  char			*str;

  my_printf(1, "x :\n");
  str = get_next_line(0);
  tmp->x = ((str[0] != '\0') ? (my_atof(str)) : (tmp->x));
  free(str);
  my_printf(1, "y :\n");
  str = get_next_line(0);
  tmp->y = ((str[0] != '\0') ? (my_atof(str)) : (tmp->y));
  free(str);
  my_printf(1, "z :\n");
  str = get_next_line(0);
  tmp->z = ((str[0] != '\0') ? (my_atof(str)) : (tmp->z));
  return (0);
}

char			edit_material_id(t_prog *prog, char mat)
{
  char			flag;
  char			tmp;
  char			*str;

  flag = 0;
  while (flag != 1)
    {
      my_printf(1, "material id :\n");
      str = get_next_line(0);
      if ((check_material_id(prog, my_getnbr(str)) == 1) || str[0] == '\0')
	{
	  if (str[0] == '\0')
	    tmp = mat;
	  else
	    tmp = (char) my_getnbr(str);
	  flag = 1;
	}
      else
	my_printf(1, "Error : material id %d don't exist\n", my_getnbr(str));
      free(str);
    }
  return (tmp);
}

int			edit_sphere(t_prog *prog, t_sphere *sph)
{
  char 			*str;

  my_printf(1, "Laissez vide si vous voulez concerver la valeur\nPoint du centre :\n");
  edit_coord(&sph->center);
  my_printf(1, "radius :\n");
  str = get_next_line(0);
  sph->radius = ((str[0] != '\0') ? (my_getnbr(str)) : (sph->radius));
  free(str);
  sph->material = edit_material_id(prog, sph->material);
  return (0);
}

int			edit_plan(t_prog *prog, t_plan *pla)
{
  my_printf(1, "Laissez vide si vous voulez concerver la valeur\n");
  my_printf(1, "Point central du plan :\n");
  edit_coord(&pla->center);
  my_printf(1, "Direction du plan :\n");
  edit_coord(&pla->dir);
  pla->material = edit_material_id(prog, pla->material);
  return (0);
}

int			edit_triangle(t_prog *prog, t_triangle *tri)
{
  my_printf(1, "Laissez vide si vous voulez concerver la valeur\n");
  my_printf(1, "Premier point du triangle :\n");
  edit_coord(&tri->angle[0]);
  my_printf(1, "Second point du triangle :\n");
  edit_coord(&tri->angle[1]);
  my_printf(1, "Troisième point du triangle :\n");
  edit_coord(&tri->angle[2]);
  tri->material = edit_material_id(prog, tri->material);
  return (0);
}

int			edit_cylindre(t_prog *prog, t_cylin *cyl)
{
  char			*str;

  my_printf(1, "Laissez vide si vous voulez concerver la valeur\n");
  my_printf(1, "Coordonées de centre\n");
  edit_coord(&cyl->center);
  my_printf(1, "Coordonées de direction\n");
  edit_coord(&cyl->dir);
  my_printf(1, "Entrez le rayon");
  str = get_next_line(0);
  cyl->radius = ((str[0] != 0) ? (my_getnbr(str)) : (cyl->radius));
  free(str);
  my_printf(1, "Entrez la hauteur");
  str = get_next_line(0);
  cyl->height = ((str[0] != 0) ? (my_getnbr(str)) : (cyl->height));
  free(str);
  cyl->material = edit_material_id(prog, cyl->material);
  return (0);
}

int			edit_cone(t_prog *prog, t_cone *con)
{
  char			*str;

  my_printf(1, "Laissez vide si vous voulez concerver la valeur\n");
  my_printf(1, "Coordonées de centre\n");
  edit_coord(&con->center);
  my_printf(1, "Coordonées de direction\n");
  edit_coord(&con->dir);
  my_printf(1, "Entrez le rayon :\n");
  str = get_next_line(0);
  con->radius = ((str[0] != 0) ? (my_getnbr(str)) : (con->radius));
  free(str);
  my_printf(1, "Entrez la hauteur :\n");
  str = get_next_line(0);
  con->height = ((str[0] != 0) ? (my_getnbr(str)) : (con->height));
  free(str);
  con->material = edit_material_id(prog, con->material);
  return (0);
}

int			edit_obj(t_prog *prog)
{
  int			id;
  int			flag;
  char			*str;
  t_obj_list		*obj;
  t_pill		*pill;

  flag = 0;
  if (prog->editor->fd == -1)
    return (put_error(ERR_NOFD));
  while (flag != 1)
    {
      my_printf(1, "Entrez l'id de l'objet a modifier (ex : 1 pour obj1):\n");
      if ((str = get_next_line(0)) == NULL)
	return (-1);
      id = (count_object(prog)) - my_getnbr(str);
      if (check_obj_id(prog, id) != 1 && id != count_object(prog))
	my_printf(1, "l'id %d n'existe pas !", (count_object(prog) - id));
      else
	flag = 1;
    }
  if ((aff_obj_spec(prog, id)))
    return (-1);
  obj = get_obj_ptr(prog, id);
  if (obj->type == 's')
    edit_sphere(prog, (t_sphere *)obj->obj);
  if (obj->type == 't')
    edit_triangle(prog, (t_triangle *)obj->obj);
  if (obj->type == 'p')
    edit_plan(prog, (t_plan *)obj->obj);
  if (obj->type == 'c')
    edit_cone(prog, (t_cone *)obj->obj);
  if (obj->type == 'y')
    edit_cylindre(prog, (t_cylin *)obj->obj);
  if (obj->type == 'l')
    {
      pill = (t_pill *)obj->obj;
      edit_cylindre(prog, pill->cylin);
    }
  return (0);
}
