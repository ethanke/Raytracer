/*
** comunicate.c for server in /Users/leandr_g/Documents/Shared folder/testServer/server_src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sat May  7 03:36:00 2016 Gaëtan Léandre
** Last update Sun May  8 01:00:26 2016 Gaëtan Léandre
*/

#include		"server.h"

int			read_client(SOCKET sock, char *buffer)
{
   int			verif;

   if ((verif = recv(sock, buffer, BUF_SIZE, 0)) < 0)
   {
      printf("Erreur de réception\n");
      verif = 0;
   }
   buffer[verif] = '\0';
   return (verif);
}

void			write_client(SOCKET sock, char *buffer)
{
   if(send(sock, buffer, my_strlen(buffer), 0) < 0)
    printf("Erreur de transfers\n");
}

void			write_all_client(t_connected *co, char *buffer,
					 int exept)
{
  t_client		*tmp;

  if (co->master != NULL && exept != co->master->sock)
    write_client(co->master->sock, buffer);
  tmp = co->clients;
  while (tmp)
    {
      if (exept != tmp->sock)
	write_client(tmp->sock, buffer);
      tmp = tmp->next;
    }
}
