/*
** xml.h for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 05:03:42 2016 victor sousa
** Last update Fri May 20 03:39:32 2016 Gaëtan Léandre
*/

#ifndef			XML_H_
# define		XML_H_

# include		"client.h"

char			*get_field(char **scene, char *field);
int			how_much_char(char *str, char to_find);
int			contains_char(char *str, char to_find);

#endif		      /*XML_H*/
