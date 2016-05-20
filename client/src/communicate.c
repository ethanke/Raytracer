/*
** comunicate.c for client in /Users/leandr_g/Documents/Shared folder/testServer/client_src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sat May  7 04:54:52 2016 Gaëtan Léandre
** Last update Fri May 20 03:41:29 2016 Gaëtan Léandre
*/

#include		"client.h"

int			read_server(SOCKET sock, char *buffer)
{
   int 			verif;

   if ((verif = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      my_printf(2, "Erreur de reception\n");
      verif = 0;
   }
   buffer[verif] = '\0';
   return verif;
}

void			write_server(SOCKET sock, char *buffer)
{
   if (send(sock, buffer, my_strlen(buffer), 0) < 0)
    my_printf(2, "Erreur de transfers\n");
}
