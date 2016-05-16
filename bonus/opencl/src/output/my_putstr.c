/*
** my_putstr.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Tue Mar  8 22:19:05 2016 victor sousa
** Last update Tue Mar  8 22:19:14 2016 victor sousa
*/

#include	"main.h"

void		my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    my_putchar(str[i++]);
}
