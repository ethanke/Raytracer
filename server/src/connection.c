/*
** connection.c for server in /Users/leandr_g/Documents/Shared folder/testServer/server_src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sat May  7 05:55:56 2016 Gaëtan Léandre
** Last update Tue May 10 18:03:46 2016 Gaëtan Léandre
*/

#include		"server.h"

void			add_client(SOCKET sock, t_connected *co, fd_set fdset)
{
  SOCKADDR_IN		csock_addr;
  t_client		*client;
  t_client		*tmp;
  SOCKET		csock;
  socklen_t		size;

  size = sizeof(csock_addr);
  if ((csock = accept(sock, (SOCKADDR *)&csock_addr, &size)) == -1)
    return;
  if ((client = malloc(sizeof(t_client))) == NULL || co->size++ < 0)
    return;
  client->sock = csock;
  client->next = NULL;
  tmp = co->clients;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  client->prev = tmp;
  if (tmp == NULL)
    co->clients = client;
  else
    tmp->next = client;
  client->sock_addr = csock_addr;
  FD_SET(csock, &fdset);
  co->max = csock > co->max ? csock : co->max;
  printf("Nouveau client : %s\n", inet_ntoa(csock_addr.sin_addr));
}

void			deco_client(t_connected *co, t_client *client)
{
  t_client		*tmp;

  if (client->prev == NULL)
    co->clients = client->next;
  co->size--;
  if (client->next != NULL)
    client->next->prev = client->prev;
  if (client->prev != NULL)
    client->prev->next = client->next;
  if (co->max == client->sock)
    {
      tmp = co->clients;
      co->max = 0;
      while (tmp)
	{
	  if (tmp->sock > co->max)
	    co->max = tmp->sock;
	  tmp = tmp->next;
	}
      co->max = (co->master && co->master->sock > co->max) ? co->master->sock
	  : co->max;
    }
  printf("Déconnection de %s\n", inet_ntoa(client->sock_addr.sin_addr));
  close(client->sock);
  free(client);
}

void			deco_master(t_connected *co)
{
  t_client		*tmp;

  if (co->max == co->master->sock)
    {
      tmp = co->clients;
      co->max = 0;
      while (tmp)
	{
	  if (tmp->sock > co->max)
	    co->max = tmp->sock;
	  tmp = tmp->next;
	}
    }
  printf("Déconnection du chef de serveur : %s\n",
	 inet_ntoa(co->master->sock_addr.sin_addr));
  close(co->master->sock);
  free(co->master);
  co->master = NULL;
}
