/*
** cmd.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Tue Apr 26 10:04:58 2016 Ethan Kerdelhue
** Last update Tue Apr 26 10:05:15 2016 Ethan Kerdelhue
*/

#include		"main.h"

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
  cmd[3].index = "write_xml";
  cmd[3].ptr = &write_xml;
  cmd[3].desc = "ecrit le contenu actuellement load dans un fichier xml";
  cmd[4].index = "END";
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