/*
** command.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/client/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Wed May 11 00:37:45 2016 Gaëtan Léandre
** Last update Sun May 15 20:52:29 2016 Gaëtan Léandre
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

  if (!my_strcmp(tab[0], "launch") && tab[1])
    {
      if (!my_strcmp(tab[1], "s") && tab[2] && !tab[3])
	{
	  my_printf(1, "Ouverture du fichier\n");
	  if ((str = read_file_to_char(tab[2])) == NULL)
	    {
	      my_printf(1, "Path fichier invalide\n");
	      write_server(sock, "error");
	    }
	  else
	    {
	      write_server(sock, "ok");
              my_printf(1, "Envois du fichier au serveur\n");
	      if (send_file(sock, str, my_strlen(str)) == 0)
		*status = -1;
	    }
	  return ("k");
	}
      else if (!my_strcmp(tab[1], "r") && !tab[2])
	{
	  my_printf(1, "Reception d'un fichier depuis le serveur\n");
	  if ((str = reciv_file(sock)) == NULL)
	    *status = -1;
	  else
	    *status = 2;
	  return (str);
	}
      else
	my_printf(1, "%s %d\n", tab[1], tab[1][1]);
    }
  return (NULL);
}

int			exit_cmd(int *status, char **tab)
{
  if (tab[0] && !my_strcmp(tab[0], "halt"))
    {
      my_printf(1, "Arret du serveur\n");
      *status = -1;
      return (1);
    }
  return (0);
}

char			*download_cmd(int *status, char **tab, t_prog *prog, SOCKET sock)
{
  char			*grille;
  int			size;
  int			wait;
  int			tmp;

  if (tab[0] && !my_strcmp(tab[0], "download") && tab[1] && tab[2])
    {
      my_printf(1, "Reception de l'image.");
      prog->win_size.x = my_getnbr(tab[1]);
      prog->win_size.y = my_getnbr(tab[2]);
      my_printf(1, "%d %d\n", prog->win_size.x, prog->win_size.y);
      wait = prog->win_size.x * prog->win_size.y;
      wait *= sizeof(unsigned int);
      grille = malloc(wait);
      if (grille != NULL)
	{
	  write_server(sock, "k");
	  size = 0;
	  tmp = 0;
	  while (size < wait && tmp > 0)
	    {
	      tmp = recv(sock, &grille[size], wait - size , 0);
	      size += tmp;
	    }
	}
      else
	write_server(sock, "n");
      if (grille != NULL && tmp >= 0)
	{
	  *status = 3;
	  return (grille);
	}
    }
  return (NULL);
}

void			cpy_in_pix(t_prog *prog, unsigned int *grille,
				   int *status)
{
  int			i;
  int			max;

  max = prog->win_size.x * prog->win_size.y;
  if (create_pix(prog) || create_win(prog))
    {
      *status = -1;
      return;
    }
  i = 0;
  while (i < max)
    {
      ((t_color *)prog->pix->pixels)[i].full = grille[i];
      i++;
    }
}

char			*exec_command(SOCKET sock, char **tab, int *status, t_prog *prog)
{
  char			*str;
  char			*grille;

  grille = NULL;
  if ((str = launch_cmd(sock, tab, status)) == NULL && exit_cmd(status, tab) == 0
      && (grille = download_cmd(status, tab, prog, sock)) == NULL)
    my_printf(2, "Commande recue erronée\n");
  if (grille != NULL)
    {
      cpy_in_pix(prog, (unsigned int *)grille, status);
      free(grille);
    }
  return (str);
}
