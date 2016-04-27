/*
** my_atof.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/utils/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Wed Apr 27 14:23:08 2016 Ethan Kerdelhue
** Last update Wed Apr 27 16:07:42 2016 Ethan Kerdelhue
*/

#include	"main.h"

int	my_isnum(char ch)
{
  return ((ch >= '0' && ch <= '9') ? 1 : 0);
}

double		my_atof(char *str)
{
  double	val;
  int		e;

  e = 0;
  val = 0.0;
  while (*str != '\0' && my_isnum(*str) == 1)
    val = val * 10.0 + (*str++ - '0');
  if (*str == '.')
  {
    while (*str != '\0' && my_isnum(*str) == 1)
    {
      val = val * 10.0 + (*str++ - '0');
      e -= 1;
    }
  }
  while (e++ < 0)
    val *= 0.1;
  return (val);
}
