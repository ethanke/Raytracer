/*
** get_xml.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Mon Apr 25 03:54:51 2016 Ethan Kerdelhue
** Last update Wed Apr 27 09:46:17 2016 Ethan Kerdelhue
*/

#include		"main.h"

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

int			add_obj_sphere(t_prog *prog)
{
  t_sphere		tmp;
  char			*str;
  int			flag;

  flag = 0;
  my_printf(0, "Coordonée du point central :\nx :\n");
  str = get_next_line(0);
  tmp.center.x = my_getnbr(str);
  free(str);
  my_printf(0, "y :\n");
  str = get_next_line(0);
  tmp.center.y = my_getnbr(str);
  free(str);
  my_printf(0, "z :\n");
  str = get_next_line(0);
  tmp.center.z = my_getnbr(str);
  free(str);
  my_printf(0, "rayon :\n");
  str = get_next_line(0);
  tmp.radius = my_getnbr(str);
  free(str);
  while (flag != 1)
    {
      my_printf(0, "material id :\n");
      str = get_next_line(0);
      tmp.material = (char) my_getnbr(str);
      if (check_material_id(prog, tmp.material) == 1)
	flag = 1;
      else
	my_printf(0, "material_id %d do not exist !\n", (int) tmp.material);
    }
  push_sphere(prog, tmp);
  return (0);
}

int			add_obj(t_prog *prog)
{
  char			*str;

  my_printf(0, "Quelle objet voulez-vous rajoutez ?\n 1 - Sphere\n 2 - Triangle\n");
  str = get_next_line(0);
  if (my_strcmp(str, "1") == 0)
    add_obj_sphere(prog);
  else
    my_printf(0, "Error : Your choice has no result\n");
  return (0);
}

int			aff_help(t_prog *prog)
{
  int			i;

  i = 0;
  while (my_strncmp(prog->editor->cmd[i].index, "END", 3))
    {
      my_putstr(prog->editor->cmd[i].index);
      my_putstr(" : ");
      my_putstr(prog->editor->cmd[i].desc);
      my_putstr("\n");
      i++;
    }
  return (0);
}

int			fill_struct(t_prog *prog)
{
 /* load_scene(prog, "scene/olympiques.xml");
  prog->editor->fd = open("scene/olympiques.xml", O_RDONLY);
  my_putstr("scene loading success!\n"); */
   if (my_access(prog->editor->arg[1]) == 0)
    return (put_error(ERR_NOACC));
  if (prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 1] == 'l' &&
      prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 2] == 'm' &&
      prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 3] == 'x' &&
      prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 4] == '.')
    load_scene(prog, prog->editor->arg[1]);
  else if (prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 1] == 'j' &&
	   prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 2] == 'b' &&
	   prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 3] == 'o' &&
	   prog->editor->arg[1][my_strlen(prog->editor->arg[1]) - 4] == '.')
    load_obj_file(prog, prog->editor->arg[1]);
  prog->editor->fd = open(prog->editor->arg[1], O_RDONLY);
  return (0);
}

char			*get_type(char c)
{
  if (c == 's')
    return ("sphere\0");
  if (c == 't')
    return ("triangle\0");
  return (NULL);
}

int			aff_xml(t_prog *prog)
{
  int			fd;

  fd = 0;
  if (prog->editor->fd == -1)
    return (put_error(ERR_NOFD));
  my_printf(fd, "<scene>\n");
  aff_win_prop(fd, prog);
  aff_mat_list(fd, prog);
  aff_obj_list(fd, prog);
  aff_light_list(fd, prog);
  my_printf(fd, "</scene>\n");
  return (0);
}

void			editor(void)
{
  t_prog		*prog;
  t_cmd			cmd;
  char			*str;

  prog = malloc(sizeof(t_prog));
  prog->editor = malloc(sizeof(t_editor));
  prog->editor->cmd = init_cmd(&cmd);
  prog->editor->fd = -1;
  while (1)
    {
      disp_info();
      str = get_next_line(0);
      prog->editor->arg = str_to_wordtab(str, " ");
      put_error(check_cmd(prog));
    }
  free(str);
}
