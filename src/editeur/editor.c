/*
** get_xml.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Mon Apr 25 03:54:51 2016 Ethan Kerdelhue
** Last update Tue Apr 26 02:54:07 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			put_error(int error)
{
  if (error == ERR_NOCMD)
    my_putstr("Error : No entry for this command use \"help\" for more details\n");
  if (error == ERR_NOACC)
    my_putstr("Error : No access to this file\n");
  if (error == ERR_NOSTR)
    my_putstr("\n");
  if (error == ERR_NOFD)
    my_putstr("Error : you need to open a .xml file before use command\n");
  return (-1);
}

void			free_tab(char **tab)
{
  int			i;

  i = 0;
  while (tab[i])
    {
      free(tab);
      i++;
    }
}

int			my_access(char *file)
{
  if (access(file, F_OK) == 0)
    return (1);
  return (0);
}

void			disp_info()
{
  my_putstr("$> ");
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
  load_scene(prog, "scene/olympiques.xml");
  prog->editor->fd = open("scene/olympiques.xml", O_RDONLY);
  my_putstr("scene loading success!\n");
  /* if (my_access(prog->editor->arg[1]) == 0)
    return (put_error(ERR_NOACC));
  if (load_scene(prog, prog->editor->arg[1]) == 0)
    my_putstr("scene loading success!\n");
  prog->editor->fd = open(prog->editor->arg[1], O_RDONLY); */
  return (0);
}

int			aff_win_prop(int fd, t_prog *prog)
{
  my_printf(fd, "\t<view>\n");
  my_printf(fd, "\t\t<x_size>");
  my_printf(fd, "%d", prog->win_size.x);
  my_printf(fd, "</x_size>\n");
  my_printf(fd, "\t\t<y_size>");
  my_printf(fd, "%d", prog->win_size.y);
  my_printf(fd, "</y_size>\n");
  my_printf(fd, "\t\t<cam_pos>\n\t\t\t<x>%d</x>\n", prog->cam_pos.x);
  my_printf(fd, "\t\t\t<y>%d</y>\n\t\t\t<z>%d</z>\n\t\t</cam_pos>\n",
	    prog->cam_pos.x, prog->cam_pos.y);
  my_printf(fd, "\t</view>\n");
  return (0);
}

int			count_material(t_prog *prog)
{
  int			i;
  t_mat_list		*tmp;

  tmp = prog->mat_list;
  i = 0;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

int			count_object(t_prog *prog)
{
  int			i;
  t_obj_list		*tmp;

  tmp = prog->obj_list;
  i = 0;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

int			aff_mat(int fd, t_mat_list *mat)
{
  my_printf(fd, "\t\t<red>%d</red>\n", mat->color.argb[RED_CMP]);
  my_printf(fd, "\t\t<green>%d</green>\n", mat->color.argb[GREEN_CMP]);
  my_printf(fd, "\t\t<blue>%d</blue>\n", mat->color.argb[BLUE_CMP]);
  my_printf(fd, "\t\t<reflect>%d</reflect>\n", mat->reflect);
  return (0);
}

int			aff_mat_list(int fd, t_prog *prog)
{
  int			i;
  t_mat_list		*tmp;

  i = 0;
  tmp = prog->mat_list;
  my_printf(fd, "\t<material_list>\n");
  my_printf(fd, "\t\t<count>");
  my_printf(fd, "%d", count_material(prog));
  my_printf(fd, "</count>\n");
  while (tmp != NULL)
    {
      i++;
      my_printf(fd, "\t<");
      my_printf(fd, my_strcatpp("mat", my_itoa(i)));
      my_printf(fd, ">\n");
      aff_mat(fd, tmp);
      my_printf(fd, "\t</");
      my_printf(fd, my_strcatpp("mat", my_itoa(i)));
      my_printf(fd, ">\n");
      tmp = tmp->next;
    }
  my_printf(fd, "\t</material_list>\n");
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

int			aff_obj(int fd, t_obj_list *obj)
{
  t_sphere *tmp;

  if (obj->type == 's')
    {

      tmp = (t_sphere *) obj->obj;
      my_printf(fd, "\t\t<center>\n\t\t\t<x>%f<x>\n", tmp->center.x);
      my_printf(fd, "\t\t\t<y>%f</y>\n\t\t\t<z>%f</x>\n", tmp->center.y,
		tmp->center.z);
      my_printf(fd, "\t\t</center>");
      my_printf(fd, "\t\t<radius>%d</radius>\n", tmp->radius);
      my_printf(fd, "\t\t<material_id>%c</matierial_id>\n", tmp->material);
    }
  return (0);
}

int			aff_obj_list(int fd, t_prog *prog)
{
  int			i;
  t_obj_list		*tmp;

  i = 0;
  tmp = prog->obj_list;
  my_printf(fd, "\t<object_list>\n");
  my_printf(fd, "\t\t<count>%d</count>\n", count_object(prog));
  while (tmp != NULL)
    {
      i++;
      my_printf(fd, "\t<obj%d>\n", i);
      my_printf(fd, "\t\t<type>%s</type>\n", get_type(tmp->type));
      aff_obj(fd, tmp);
      my_printf(fd, "\t</obj%d>\n", i);
      tmp = tmp->next;
    }
  return (0);
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
  my_printf(fd, "</scene>\n");
  return (0);
}

t_cmd			*init_cmd()
{
  t_cmd			*cmd;

  cmd = malloc(sizeof(t_cmd) * 10);
  cmd[0].index = "help";
  cmd[0].ptr = &aff_help;
  cmd[0].desc = "affiche une aide pour l'utilisateur";
  cmd[1].index = "load_xml";
  cmd[1].ptr = &fill_struct;
  cmd[1].desc = "load un fichier .xml dans le shell";
  cmd[2].index = "aff_xml";
  cmd[2].ptr = &aff_xml;
  cmd[2].desc = "affiche le contenu du fichier xml actuel";
  cmd[3].index = "END";
  return (cmd);
}

int			check_cmd(t_prog *prog)
{
  int			ret;
  int			i;

  i = 0;
  ret = -1;
  if (prog->editor->arg[0] == NULL)
    ret = ERR_NOSTR;
  while (my_strncmp(prog->editor->cmd[i].index, "END", 3) && ret == -1)
    {
      if (my_strncmp(prog->editor->cmd[i].index, prog->editor->arg[0],
		     my_strlen(prog->editor->cmd[i].index)) == 0)
	{
	  prog->editor->cmd[i].ptr(prog);
	  ret += 1;
	}
      i++;
    }
  return (ret);
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
