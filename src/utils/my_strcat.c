/*
** my_strcat.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Tue Mar  8 17:58:27 2016 victor sousa
** Last update Fri Mar 11 00:19:15 2016 victor sousa
*/

#include	"main.h"

char		*my_strcat(char *dest, char *src)
{
  int		len;
  int		i;

  len = my_strlen(dest);
  i = 0;
  while (src[i])
    {
      dest[len + i] = src[i];
      i = i + 1;
    }
  dest[len + i] = '\0';
  return (dest);
}
