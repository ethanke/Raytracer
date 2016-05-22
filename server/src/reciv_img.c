/*
** reciv_img.c for server in /Users/leandr_g/Documents/Shared folder/testServer/server_src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sun May  8 02:00:53 2016 Gaëtan Léandre
** Last update Sun May 22 19:13:16 2016 Philippe Lefevre
*/

#include		"server.h"

void			fill_end(t_client *client, unsigned int *tmp,
				 t_connected *co)
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
	    co->end[pos + co->width * y] = COLOR_DEF;
	  else
	    co->end[pos + co->width * y] = tmp[x + y
	      * (client->end_x - client->start_x)];
	  pos++;
	  x++;
	}
      y++;
    }
  if (tmp != NULL)
    free(tmp);
}

void			recive_img_sock(t_connected *co, t_client *client,
					fd_set *fdset)
{
  int			tmp;

  if (FD_ISSET(client->sock, fdset))
    {
      if (client->grille != NULL)
	{
	  tmp = recv(client->sock, &(client->grille)[client->pos],
		     client->wait - client->pos, 0);
	  client->pos += tmp >= 0 ? tmp : 0;
	}
      if (client->wait <= client->pos && client->done != 1)
	{
	  fill_end(client, (unsigned int *)client->grille, co);
	  client->done = 1;
	}
      else if (tmp <= 0 && client->done != 1)
	{
	  fill_end(client, NULL, co);
	  client->done = -1;
	}
    }
}

int			test_done(t_connected *co)
{
  t_client		*tmp;

  if (co->master->done == 0)
    return (0);
  tmp = co->clients;
  while (tmp)
    {
      if (tmp->done == 0)
	return (0);
      tmp = tmp->next;
    }
  return (1);
}

void			reciv_img_end(t_connected *co, fd_set *fdset,
				      t_client *tmp)
{
  while (tmp != NULL)
    {
      recive_img_sock(co, tmp, fdset);
      tmp = tmp->next;
    }
  if (test_done(co) == 1)
    {
      my_printf(1, "L'obj a bien été reçu. /download avec "
		"l'acces root pour le récupérer\n");
      write_all_client(co, "L'obj a bien été reçu. /download "
		       "avec l'acces root pour le récupérer", -1);
      co->status = 0;
    }
}

void			reciv_img(t_connected *co)
{
  fd_set		fdset;
  t_client		*tmp;

  if ((co->end =
       malloc(sizeof(unsigned int) * co->width * co->height)) == NULL)
    co->status = -1;
  while (co->status == 1)
    {
      FD_ZERO(&fdset);
      FD_SET(co->master->sock, &fdset);
      tmp = co->clients;
      while (tmp != NULL)
	{
	  FD_SET(tmp->sock, &fdset);
	  tmp = tmp->next;
	}
      if (select(co->max + 1, &fdset, NULL, NULL, NULL) == -1)
	co->status = -1;
      recive_img_sock(co, co->master, &fdset);
      tmp = co->clients;
      reciv_img_end(co, &fdset, tmp);
    }
}

void			charge_server_end(t_connected *co,
					  int size_x, int actu_x)
{
  int			i;
  char			*str;
  t_client		*tmp;

  tmp = co->clients;
  while (tmp)
    {
      tmp->start_x = actu_x;
      tmp->end_x =
      (actu_x + size_x >= co->width) ? co->width : actu_x + size_x;
      actu_x = tmp->end_x;
      str = my_sprintf("%d %d %c", tmp->start_x, tmp->end_x,
		       (co->form == 1 ? 'x' : 'o'));
      tmp->done = 0 * (tmp->pos = 0);
      tmp->wait =
      (tmp->end_x - tmp->start_x) * co->height * sizeof(unsigned int);
      tmp->grille = malloc(tmp->wait);
      i = 0;
      while (tmp->grille != NULL && i < tmp->wait)
	tmp->grille[i++] = 0;
      write_client(tmp->sock, str);
      free(str);
      tmp = tmp->next;
    }
}

void			charge_server_beg(int *i, int *size_x, int *actu_x,
					  t_connected *co)
{
  *i = 0;
  while (*i++ < 2000000000);
  my_printf(1, "Envois des consignes aux clients\n");
  *size_x = co->width / (co->size + 1) + 1;
  *actu_x = 0;
}

int			charge_server(t_connected *co)
{
  char			*str;
  int			size_x;
  int			actu_x;
  int			i;

  charge_server_beg(&i, &size_x, &actu_x, co);
  co->master->start_x = actu_x;
  co->master->end_x =
    (actu_x + size_x >= co->width) ? co->width : actu_x + size_x;
  co->master->wait = (co->master->end_x - co->master->start_x)
    * co->height * sizeof(unsigned int);
  if ((co->master->grille = malloc(co->master->wait)) == NULL)
    return (-1);
  i = 0;
  while (co->master->grille != NULL && i < co->master->wait)
    co->master->grille[i++] = 0;
  actu_x = co->master->end_x;
  str = my_sprintf("%d %d %c", co->master->start_x, co->master->end_x,
		   (co->form == 1 ? 'x' : 'o'));
  co->master->done = 0 * (co->master->pos = 0);
  write_client(co->master->sock, str);
  free(str);
  charge_server_end(co, size_x, actu_x);
  return (1);
}
