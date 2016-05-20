/*
** client.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/client/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Tue May 10 22:52:42 2016 Gaëtan Léandre
** Last update Fri May 20 03:41:25 2016 Gaëtan Léandre
*/

#include		"client.h"

void			push_command(SOCKET sock)
{
  char			*str;

  if ((str = get_next_line(0)) != NULL && my_strlen(str) <= BUF_SIZE)
    {
      write_server(sock, str);
      free(str);
    }
  else
    my_printf(2, "Erreur de commande\n");
}

char			*recive_command(SOCKET sock, int *status, t_prog *prog)
{
  int			recive;
  char			buffer[BUF_SIZE + 1];
  char			**tab;
  char			*str;

  str = NULL;
  recive = read_server(sock, buffer);
  if (recive == 0)
    {
      *status = -1;
      my_printf(2, "La connection avec le serveur a ete perdue\n");
      return (str);
    }
  if ((tab = is_command(buffer)) == NULL)
    my_printf(1, "%s\n", buffer);
  else
    {
      str = exec_command(sock, tab, status, prog);
      free_tab(tab);
    }
  return (str);
}

void			recive_launch(SOCKET sock)
{
  int			recive;
  char			buffer[BUF_SIZE + 1];

  recive = read_server(sock, buffer);
  if (recive == 0)
    my_printf(2, "La connection avec le serveur a ete perdue\n");
  my_printf(1, "%s\n", buffer);
}

int			set_connections(SOCKET sock, t_prog *prog)
{
  fd_set		fdset;
  int			status;
  char			*str;

  status = 0;
  while (status != -1)
    {
      status = 0;
      while (status == 0)
	{
	  FD_ZERO(&fdset);
	  FD_SET(STDIN_FILENO, &fdset);
	  FD_SET(sock, &fdset);
	  if (select(sock + 1, &fdset, NULL, NULL, NULL) == -1)
	    return (-1);
	  if (FD_ISSET(STDIN_FILENO, &fdset))
	    push_command(sock);
	  else if (FD_ISSET(sock, &fdset))
	    str = recive_command(sock, &status, prog);
	}
      if (status == 2)
	client_raytrace(str, &status, sock);
      else if (status == 3)
	return (status);
    }
  return (status);
}

SOCKET			init_connection()
{
  SOCKET		sock;
  SOCKADDR_IN		sock_addr;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      my_printf(2, "Erreur de socket\n");
      return (-1);
    }
  sock_addr.sin_addr.s_addr = inet_addr("93.9.51.53");
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(PORT);
  if (connect(sock, (SOCKADDR*)&sock_addr, sizeof(sock_addr)) == -1)
    {
      my_printf(2, "Pas de connection\n");
      return (-1);
    }
  return (sock);
}

int			client(t_prog *prog)
{
  SOCKET		sock;
  int			status;

  if ((sock = init_connection()) == -1)
    return (-1);
  status = set_connections(sock, prog);
  close(sock);
  return (status);
}
