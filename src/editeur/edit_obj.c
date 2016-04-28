/*
** edit_obj.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Wed Apr 27 18:31:29 2016 Ethan Kerdelhue
** Last update Thu Apr 28 11:32:05 2016 Ethan Kerdelhue
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
	  my_printf(0, "Error : id %d don't found", id);
	  return (-1);
	}
    }
  my_printf(0, "\t<obj%d>\n", (count_object(prog) - id));
  my_printf(0, "\t\t<type>%s</type>\n", get_type(tmp->type));
  aff_obj(0, tmp);
  my_printf(0, "\t</obj%d>\n", (count_object(prog) - id));
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
      i++;
      if (id == i)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

t_obj_list		*get_obj_ptr(t_prog *prog, int id)
{
  t_obj_list		*tmp;
  int			i;

  i = 0;
  tmp = prog->obj_list;
  while (tmp != NULL)
    {
      i++;
      if (id == i)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

int			edit_coord(t_coord *tmp)
{
  char			*str;

  my_printf(0, "x :\n");
  str = get_next_line(0);
  tmp->x = ((str != NULL) ? (my_atof(str)) : (tmp->x));
  free(str);
  my_printf(0, "y :\n");
  str = get_next_line(0);
  tmp->y = ((str != NULL) ? (my_atof(str)) : (tmp->y));
  free(str);
  my_printf(0, "z :\n");
  str = get_next_line(0);
  tmp->z = ((str != NULL) ? (my_atof(str)) : (tmp->z));
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
      my_printf(0, "material id :\n");
      str = get_next_line(0);
      if ((check_material_id(prog, (char) my_getnbr(str)) == 1) || str == NULL)
	{
	  if (str == NULL)
	    tmp = mat;
	  else
	    tmp = (char) my_getnbr(str);
	  flag = 1;
	}
      else
	my_printf(0, "Error : material id %d don't exist\n", my_getnbr(str));
      free(str);
    }
  return (tmp);
}

int			edit_sphere(t_prog *prog, t_sphere *sph)
{
  char 			*str;

  my_printf(0, "Laissez vide si vous voulez concerver la valeur\nPoint du centre :\n");
  edit_coord(&sph->center);
  my_printf(0, "radius :\n");
  str = get_next_line(0);
  sph->radius = ((str != NULL) ? (my_getnbr(str)) : (sph->radius));
  free(str);
  sph->material = edit_material_id(prog, sph->material);
  return (0);
}


int			edit_triangle(t_prog *prog, t_triangle *tri)
{
  (void) prog;
  (void) tri;
  return (0);
}
int			edit_obj(t_prog *prog)
{
  int			id;
  int			flag;
  char			*str;
  t_obj_list		*obj;

  flag = 0;
  if (prog->editor->fd == -1)
    return (put_error(ERR_NOFD));
  while (flag != 1)
    {
      my_printf(0, "Entrez l'id de l'objet a modifier (ex : 1 pour obj1):\n");
      str = get_next_line(0);
      id = count_object(prog) - my_getnbr(str);
      if (check_obj_id(prog, id) != 1)
	my_printf(0, "l'id %d n'existe pas !", (count_object(prog) - id));
      else
	flag = 1;
    }
  aff_obj_spec(prog, id);
  obj = get_obj_ptr(prog, id);
  if (obj->type == 's')
    edit_sphere(prog, (t_sphere *)obj->obj);
  if (obj->type == 't')
    edit_triangle(prog, (t_triangle *)obj->obj);
  return (0);
}
