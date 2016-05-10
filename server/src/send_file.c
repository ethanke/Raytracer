/*
** send_file.c for commun in /Users/leandr_g/Documents/Shared folder/testServer/commun/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sun May  8 03:45:09 2016 Gaëtan Léandre
** Last update Tue May 10 23:42:45 2016 Gaëtan Léandre
*/

#include		"server.h"

char			*reciv_file(SOCKET sock)
{
  char			*file;
  t_size		size;
  int			verif;

  if ((verif = recv(sock, size.csize, 4, 0)) < 0)
  {
     my_printf(2, "Erreur de réception\n");
     size.i = 0;
  }
  if (size.i == 0 || (file = malloc(size.i + 1)) == NULL)
    return (NULL);
  else if ((verif = recv(sock, file, size.i, 0)) < 0)
    {
       my_printf(2, "Erreur de réception\n");
      return (NULL);
    }
  file[verif] = '\0';
  return (file);
}

int		send_file(SOCKET sock, char *file)
{
  t_size	size;

  size.i = my_strlen(file);
  if (send(sock, size.csize, 4, 0) < 0)
    return (0);
  if (send(sock, file, size.i, 0) < 0)
    return (0);
  return (1);
}
