/*
** command.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/client/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Wed May 11 00:37:45 2016 Gaëtan Léandre
** Last update Wed May 11 06:10:56 2016 Gaëtan Léandre
*/

#include		"main.h"

char			**is_command(char *str)
{
  int			i;

  i = 0;
  if (my_strlen(str) > 0)
    {
      while (str[i] && (str[i] == ' ' || str[i] == '\t'))
	i++;
      if (str[i] == '/')
	return (str_to_wordtab(&str[i + 1], " "));
    }
  return (NULL);
}

char			*read_file_to_char(char *file)
{
  char			*str;
  int			fd;
  struct stat		file_s;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (NULL);
  fstat(fd, &file_s);
  if ((str = malloc(file_s.st_size + 1)) == NULL)
    return (NULL);
  str[file_s.st_size] = '\0';
  if (read(fd, str, file_s.st_size) == -1)
    return (NULL);
  close(fd);
  return (str);
}

char			*launch_cmd(SOCKET sock, char **tab, int *status)
{
  char			*str;

  if (my_strcmp(tab[0], "launch") && tab[1])
    {
      if (my_strcmp(tab[1], "s") && tab[2] && !tab[3])
	{
	  if ((str = read_file_to_char(tab[2])) == NULL)
	    write_server(sock, "error");
	  else
	    {
	      write_server(sock, "ok");
	      if (send_file(sock, str, my_strlen(str)) == 0)
		*status = -1;
	      else
		*status = 2;
	    }
	  return ("k");
	}
      else if (my_strcmp(tab[1], "r") && !tab[2])
	{
	  if ((str = reciv_file(sock)) == NULL)
	    *status = -1;
	  return (str);
	}
    }
  return (NULL);
}

int			exit_cmd(int *status, char **tab)
{
  if (tab[0] && my_strcmp(tab[0], "halt"))
    {
      *status = -1;
      return (1);
    }
  return (0);
}

char			*exec_command(SOCKET sock, char **tab, int *status)
{
  char			*str;

  if ((str = launch_cmd(sock, tab, status)) == NULL && exit_cmd(status, tab) == 0)
    my_printf(2, "Commande recue erronée");
  return (str);
}
