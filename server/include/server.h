/*
** server.h for server in /Users/leandr_g/Documents/Shared folder/testServer/server_src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Fri May  6 22:41:13 2016 Gaëtan Léandre
** Last update Sat May 14 06:05:56 2016 Gaëtan Léandre
*/

#ifndef			_SERVER_H_
# define		_SERVER_H_

# define		PORT		777
# define		MAX_CLIENTS	100
# define		BUF_SIZE	1024
# define		PASSWD		"bonjour"
# define		COLOR_DEF	0xFF000000

# include		<sys/types.h>
# include		<sys/socket.h>
# include		<netinet/in.h>
# include		<arpa/inet.h>
# include		<unistd.h>
# include		<stdio.h>
# include		<stdlib.h>
# include		"get_next_line.h"
# include 		"utils.h"
# include		"my_sprintf.h"
# include		"my_printf.h"
# include		"xml.h"

typedef 		int SOCKET;
typedef struct 		sockaddr_in SOCKADDR_IN;
typedef struct 		sockaddr SOCKADDR;
typedef struct 		in_addr IN_ADDR;

typedef struct		s_client
{
  int			start_x;
  int			end_x;
  char			done;
  SOCKET		sock;
  SOCKADDR_IN		sock_addr;
  struct s_client	*next;
  struct s_client	*prev;
}			t_client;

typedef struct		s_connected
{
  int			size;
  int			max;
  char			form;
  char			status;
  int			width;
  int			height;
  t_client		*master;
  t_client		*clients;
}			t_connected;

int			read_client(SOCKET sock, char *buffer);
void			launch_command_server(char **tab, t_connected *co);
void			launch_command_client(SOCKET sock, char **tab,
					      t_connected *co);
void			exec_command(t_connected *co);
void			add_client(SOCKET sock, t_connected *co, fd_set fdset);
void			deco_client(t_connected *co, t_client *client);
void			deco_master(t_connected *co);
int			read_client(SOCKET sock, char *buffer);
void			write_client(SOCKET sock, char *buffer);
void			write_all_client(t_connected *co, char *buffer,
		 			 int exept);
int			charge_server(t_connected *co);
int			my_getnbr(char *str);
char			*my_strstr(char *str, char *to_find);
void			recive_and_launch(t_connected *co);
void			reciv_img(t_connected *co);

#endif			/* _SERVER_H_ */
