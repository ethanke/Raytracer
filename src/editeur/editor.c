/*
** get_xml.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Mon Apr 25 03:54:51 2016 Ethan Kerdelhue
** Last update Tue Apr 26 10:08:32 2016 Ethan Kerdelhue
*/

#include		"main.h"

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
