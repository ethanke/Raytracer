/*
** my_strlen.c for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Tue Feb  9 05:30:17 2016 victor sousa
** Last update Tue Feb  9 05:30:49 2016 victor sousa
*/

#include	"main.h"

int		my_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}
