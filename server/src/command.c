/*
** command.c for server in /Users/leandr_g/Documents/Shared folder/testServer/server_src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sat May  7 05:54:51 2016 Gaëtan Léandre
** Last update Tue May 10 23:37:25 2016 Gaëtan Léandre
*/

#include		"server.h"

int			cmd_launch(SOCKET sock, char **tab, t_connected *co)
{
  char			*str;
  t_client		*tmp;

  (void)str;
  if (tab == NULL)
    return (0);
  if (co->master && sock == co->master->sock && my_strcmp(tab[0], "launch")
      && tab[1] && tab[2] == NULL)
    {
      if (co->size <= 0)
	{
	  write_client(sock, "Pas de clients connectés pour effectuer launch");
	  return (1);
	}
      tmp = co->clients;
/*      str = sprintf("/launch s %s", tab[1]);*/
      write_client(sock, "test");
/*      free(str);*/
      while (tmp)
	{
	  write_client(tmp->sock, "/launch r");
	  tmp = tmp->next;
	}
      co->status = 1;
      return (1);
    }
  return (0);
}

int			cmd_sudo(SOCKET sock, char **tab, t_connected *co)
{
  t_client		*tmp;

  if (tab == NULL)
    return (0);
  if (my_strcmp(tab[0], "sudo") && tab[1] && my_strcmp(tab[1], PASSWD)
      && tab[2] == NULL && ((co->master && co->master->sock != sock) || !co->master))
    {
      if (co->master)
	{
	  co->master->prev = NULL;
	  co->master->next = co->clients;
	  co->clients = co->master;
	}
      else
	co->size--;
      tmp = co->clients;
      while (tmp != NULL)
	{
	  if (tmp->sock == sock)
	    {
	      if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	      else
		co->clients = tmp->next;
	      if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	      co->master = tmp;
	      my_printf(1, "Le pouvoir est renversé, un nouveau joueur s'installe à la tête du serveur!\n");
	      write_all_client(co, "Le pouvoir est renversé, un nouveau joueur s'installe à la tête du serveur!", -1);
	      return (1);
	    }
	  tmp = tmp->next;
	}
      return (0);
    }
  return (0);
}

int			cmd_exit(char **tab, t_connected *co)
{
  if (tab == NULL)
    return (0);
  if (my_strcmp(tab[0], "exit") && tab[1] == NULL)
    {
      co->status = -1;
      return (1);
    }
  return (0);
}

void			launch_command_server(char **tab, t_connected *co)
{

  if (!tab || !cmd_exit(tab, co))
    my_printf(1, "Commande inconnue\n");
  free_tab(tab);
}

void			launch_command_client(SOCKET sock, char **tab,
					      t_connected *co)
{
  if ((co->master == NULL || co->master->sock != sock || cmd_exit(tab, co) == 0)
      && cmd_sudo(sock, tab, co) == 0 && cmd_launch(sock, tab, co) == 0)
    write_client(sock, "Commande inconnue");
  free_tab(tab);
}

void			exec_command(t_connected *co)
{
  char			*str;
  char			**tab;

  if ((str = get_next_line(0)) != NULL)
    {
      tab = str_to_wordtab(str, " ");
      launch_command_server(tab, co);
      free(str);
    }
}
