/*
** reciv_img.c for server in /Users/leandr_g/Documents/Shared folder/testServer/server_src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sun May  8 02:00:53 2016 Gaëtan Léandre
** Last update Tue May 10 18:13:39 2016 Gaëtan Léandre
*/

#include		"server.h"

/*void			get_connections(SOCKET sock, t_connected *co)
{
  t_client		*tmp;
  fd_set		fdset;

  while (co->status == 0)
    {
      FD_ZERO(&fdset);
      FD_SET(STDIN_FILENO, &fdset);
      FD_SET(sock, &fdset);
      tmp = co->clients;
      while (tmp != NULL)
	{
	  FD_SET(tmp->sock, &fdset);
	  tmp = tmp->next;
	}
      if (co->master != NULL)
	FD_SET(co->master->sock, &fdset);
      if (select(co->max + 1, &fdset, NULL, NULL, NULL) == -1)
	return;
      if (FD_ISSET(STDIN_FILENO, &fdset))
	exec_command(sock, co);
      else if (FD_ISSET(sock, &fdset))
	add_client(sock, co, fdset);
      else
	action_client(sock, co, fdset);
    }
}*/

unsigned int		*fill_end(t_client *client, unsigned int *tmp, unsigned int *end, t_connected *co)
{
  int			x;
  int			y;
  int			pos;

  y = 0;
  while (y < co->height)
    {
      x = 0;
      pos = client->start_x;
      while (pos < client->end_x)
	{
	  if (tmp == NULL)
	    end[pos + co->width * y] = COLOR_DEF;
	  else
	    end[pos + co->width * y] = tmp[x + y * (client->end_x - client->start_x)];
	  pos++;
	  x++;
	}
      y++;
    }
  return (end);
}

unsigned int		*reciv_img(t_connected *co)
{
  unsigned int		*end;
  fd_set		fdset;
  t_client		*tmp;

  if ((end = malloc(sizeof(unsigned int) * co->width * co->height)) == NULL)
    return (NULL);
  while (co->status == 1)
    {
      FD_ZERO(&fdset);
      tmp = co->clients;
      while (tmp != NULL)
	{
	  FD_SET(tmp->sock, &fdset);
	  tmp = tmp->next;
	}
    }
  return (end);
}

int			charge_server(t_connected *co)
{
  t_client		*tmp;
  char			*file;
  int			size_x;
  int			actu_x;

  printf("Téléchargement du fichier sur le serveur\n");
  file = reciv_file(co->master->sock);
  if (file == NULL)
    return (-1);
  //RECUPERATION DES TAILLES DE FICHIER
  co->width = 10;
  co->height = 10;
  printf("Envois du fichier aux clients\n");
  tmp = co->clients;
  while (tmp)
    {
      send_file(tmp->sock, file);
      tmp = tmp->next;
    }
  free(file);
  printf("Envois des consignes aux clients\n");
  size_x = co->width / co->size + 1;
  actu_x = 0;
  tmp = co->clients;
  while (tmp)
    {
      tmp->start_x = actu_x;
      tmp->end_x = (actu_x + size_x >= co->width) ? co->width : actu_x + size_x;
      actu_x = tmp->end_x;
      file = my_sprintf("/run %d %d", tmp->start_x, tmp->end_x);
      tmp->done = 0;
      write_client(tmp->sock, file);
      free(file);
      tmp = tmp->next;
    }
  return (1);
}
