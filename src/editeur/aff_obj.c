/*
** aff_obj.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Tue Apr 26 09:58:54 2016 Ethan Kerdelhue
** Last update Thu May  5 02:01:30 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			aff_obj_list(int fd, t_prog *prog)
{
  int			i;
  t_obj_list		*tmp;

  i = count_object(prog) + 1;
  tmp = prog->obj_list;
  my_printf(fd, "\t<object_list>\n");
  my_printf(fd, "\t\t<count>%d</count>\n", count_object(prog));
  while (tmp != NULL)
    {
      i--;
      my_printf(fd, "\t<obj%d>\n", i);
      my_printf(fd, "\t\t<type>%s</type>\n", get_type(tmp->type));
      aff_obj(fd, tmp);
      my_printf(fd, "\t</obj%d>\n", i);
      tmp = tmp->next;
    }
  my_printf(fd, "\t</object_list>\n");
  return (0);
}

int			aff_obj_triangle(int fd, t_obj_list *obj, int i)
{
  t_triangle		*tmpt;

  while (i < 3)
    {
      tmpt = (t_triangle *) obj->obj;
      my_printf(fd, "\t\t<p%d>\n", i + 1);
      my_printf(fd, "\t\t\t<x>%f</x>\n\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n",
		 tmpt->angle[i].x, tmpt->angle[i].y, tmpt->angle[i].z);
      my_printf(fd, "\t\t</p%d>\n", i + 1);
      i++;
    }
  my_printf(fd, "\t\t<material_id>%c</material_id>\n", tmpt->material + 48);
  return (0);
}

int			aff_obj_sphere(int fd, t_obj_list *obj)
{
  t_sphere 		*tmp;

  tmp = (t_sphere *) obj->obj;
  my_printf(fd, "\t\t<center>\n\t\t\t<x>%f</x>\n", tmp->center.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n", tmp->center.y,
		  tmp->center.z);
  my_printf(fd, "\t\t</center>\n\t\t<radius>%d</radius>\n", tmp->radius);
  my_printf(fd, "\t\t<material_id>%c</matierial_id>\n", tmp->material + 48);
  return (0);
}

int			aff_obj_plan(int fd, t_obj_list *obj)
{
  t_plan		*tmp;

  tmp = (t_plan *) obj->obj;
  my_printf(fd, "\t\t<center>\n\t\t\t<x>%f</x>\n", tmp->center.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</center>\n"
	    ,tmp->center.y, tmp->center.z);
  my_printf(fd, "\t\t<dir>\n\t\t\t<x>%f<x>\n", tmp->dir.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</dir>\n"
	    ,tmp->dir.y, tmp->dir.z);
  my_printf(fd, "\t\t<material_id1>%c</matierial_id1>\n", tmp->material + 48);
my_printf(fd, "\t\t<material_id2>%c</matierial_id2>\n", tmp->material2 + 48);
  return (0);
}

int			aff_obj_cone(int fd, t_obj_list *obj)
{
  t_cone		*tmp;

  tmp = (t_cone *) obj->obj;
  my_printf(fd, "\t\t<center>\n\t\t\t<x>%f</x>\n", tmp->center.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</center>\n"
	    ,tmp->center.y, tmp->center.z);
  my_printf(fd, "\t\t<dir>\n\t\t\t<x>%f<x>\n", tmp->dir.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</dir>\n"
	    ,tmp->dir.y, tmp->dir.z);
  my_printf(fd, "\t\t<radius>%d</radius>\n", tmp->radius);
  my_printf(fd, "\t\t<height>%d</height>\n", tmp->height);
  my_printf(fd, "\t\t<material_id>%c</matierial_id>\n", tmp->material + 48);
  return (0);
}

int			aff_obj_cylindre(int fd, t_obj_list *obj)
{
  t_cylin		*tmp;

  tmp = (t_cylin *) obj->obj;
  my_printf(fd, "\t\t<center>\n\t\t\t<x>%f</x>\n", tmp->center.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</center>\n"
	    ,tmp->center.y, tmp->center.z);
  my_printf(fd, "\t\t<dir>\n\t\t\t<x>%f<x>\n", tmp->dir.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</dir>\n"
	    ,tmp->dir.y, tmp->dir.z);
  my_printf(fd, "\t\t<radius>%d</radius>\n", tmp->radius);
  my_printf(fd, "\t\t<height>%d</height>\n", tmp->height);
  my_printf(fd, "\t\t<material_id>%c</matierial_id>\n", tmp->material + 48);
  return (0);
}

int			aff_obj_pillule(int fd, t_obj_list *obj)
{
  t_cylin		*tmp;
  t_pill		*pill;

  pill = (t_pill *)obj->obj;
  tmp = pill->cylin;
  my_printf(fd, "\t\t<center>\n\t\t\t<x>%f</x>\n", tmp->center.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</center>\n"
	    ,tmp->center.y, tmp->center.z);
  my_printf(fd, "\t\t<dir>\n\t\t\t<x>%f<x>\n", tmp->dir.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</dir>\n"
	    ,tmp->dir.y, tmp->dir.z);
  my_printf(fd, "\t\t<radius>%d</radius>\n", tmp->radius);
  my_printf(fd, "\t\t<height>%d</height>\n", tmp->height);
  my_printf(fd, "\t\t<material_id>%c</matierial_id>\n", tmp->material + 48);
  return (0);
}

int			aff_obj_circle(int fd, t_obj_list *obj)
{
  t_circle		*tmp;

  tmp = (t_circle *) obj->obj;
  my_printf(fd, "\t\t<center>\n\t\t\t<x>%f</x>\n", tmp->plan.center.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</center>\n"
	    ,tmp->plan.center.y, tmp->plan.center.z);
  my_printf(fd, "\t\t<dir>\n\t\t\t<x>%f<x>\n", tmp->plan.dir.x);
  my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</z>\n\t\t</dir>\n"
	    ,tmp->plan.dir.y, tmp->plan.dir.z);
  my_printf(fd, "\t\t<radius>%d</radius>\n", (int) tmp->radius);
  my_printf(fd, "\t\t<material_id>%c</matierial_id>\n", tmp->material + 48);
  return (0);
}

int			aff_obj(int fd, t_obj_list *obj)
{
  if (obj->type == 's')
    aff_obj_sphere(fd, obj);
  if (obj->type == 't')
    aff_obj_triangle(fd, obj, 0);
  if (obj->type == 'p')
    aff_obj_plan(fd, obj);
  if (obj->type == 'c')
    aff_obj_cone(fd, obj);
  if (obj->type == 'y')
    aff_obj_cylindre(fd, obj);
  if (obj->type == 'i')
    aff_obj_circle(fd, obj);
  if (obj->type == 'l')
    aff_obj_pillule(fd, obj);
  return (0);
}
