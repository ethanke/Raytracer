/*
** client.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/client/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Tue May 10 22:52:42 2016 Gaëtan Léandre
** Last update Fri May 13 04:10:35 2016 Gaëtan Léandre
*/

#include		"main.h"

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

char			*recive_command(SOCKET sock, int *status)
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
      str = exec_command(sock, tab, status);
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

void			set_connections(SOCKET sock)
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
	    return;
	  if (FD_ISSET(STDIN_FILENO, &fdset))
	    push_command(sock);
	  else if (FD_ISSET(sock, &fdset))
	    str = recive_command(sock, &status);
	}
      if (status == 2)
	{
	  exit(0);
	  //lancement
	}
    }
  (void)str;
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
  sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(PORT);
  if(connect(sock, (SOCKADDR*)&sock_addr, sizeof(sock_addr)) == -1)
    {
      my_printf(2, "Pas de connection\n");
      return (-1);
    }
  return (sock);
}

int			client(t_prog *prog)
{
  SOCKET		sock;

  (void)prog;
  if ((sock = init_connection()) == -1)
    return (-1);
  set_connections(sock);
  close(sock);
  return (0);
}
