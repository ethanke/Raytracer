/*
** get_xml.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Mon Apr 25 03:54:51 2016 Ethan Kerdelhue
** Last update Mon Apr 25 06:26:59 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			put_error(int error)
{
  if (error == ERR_NOCMD)
    my_putstr("Error : No entry for this command use --help for more details\n");
  if (error == ERR_NOACC)
    my_putstr("Error : No access to this file\n");
  if (error == ERR_NOSTR)
    my_putstr("Error : the string are null\n");
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
  while (my_strncmp(prog->cmd[i].index, "END", 3))
    {
      my_putstr(prog->cmd[i].index);
      my_putstr(" : ");
      my_putstr(prog->cmd[i].desc);
      my_putstr("\n");
      i++;
    }
  return (0);
}

int			fill_struct(t_prog *prog)
{
  if (my_access(prog->arg[1]) == 0)
    return (put_error(ERR_NOACC));
  if (load_scene(prog, prog->arg[1]) == 0)
    my_putstr("scene loading success!\n");
}

t_cmd			*init_cmd()
{
  t_cmd			*cmd;

  cmd = malloc(sizeof(t_cmd) * 10);
  cmd[0].index = "help";
  cmd[0].ptr = &aff_help;
  cmd[0].desc = "affiche une aide pour l'utilisateur";
  cmd[1].index = "load_xml \" filepath \" ";
  cmd[1].ptr = &fill_struct;
  cmd[1].desc = "load un fichier .xml dans le shell";
  cmd[2].index = "END";
  return (cmd);
}

int			check_cmd(t_prog *prog)
{
  int			ret;
  int			i;

  i = 0;
  ret = -1;
  if (prog->arg[0] == NULL)
    ret = ERR_NOSTR;
  while (my_strncmp(prog->cmd[i].index, "END", 3) && ret == -1)
    {
      if (my_strncmp(prog->cmd[i].index, prog->arg[0],
		     my_strlen(prog->arg[0])) == 0)
	{
	  prog->cmd[i].ptr(prog);
	  ret += 1;
	}
      i++;
    }
  return (ret);
}

void			editor(void)
{
  t_prog		prog;
  t_cmd			*cmd;
  char			*str;

  prog.cmd = init_cmd(cmd);
  while (1)
    {
      disp_info();
      str = get_next_line(0);
      prog.arg = str_to_wordtab(str, " ");
      put_error(check_cmd(&prog));
    }
  free(str);
}
