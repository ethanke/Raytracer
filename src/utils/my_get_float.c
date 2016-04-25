/*
** my_get_float.c for  in /home/sousa_v/rendu/lapin/raytracer_temp/src/utils/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Mon Apr 25 09:19:12 2016 Victor Sousa
** Last update Mon Apr 25 09:23:35 2016 Victor Sousa
*/

#include		"main.h"

static int		my_getnbr_char(char p)
{
  if( (p >= '0') && (p <= '9') )
    return ((int)p - 48);
  else
    return (-1);
}

float			my_get_float(char *p)
{
  int i;
  int f;
  int count;
  int countdec;
  float result;

  i = 0;
  f = 0;
  count = 0;
  countdec = 0;
  result = 0;
  while ((p[count] != ',') && (p[count] != '\0'))
    {
      if (p[count] != ',')
	{
	  i *= 10;
	  i += my_getnbr_char(p[count]);
	}
      count++;
    }
  count++;
  while (p[count] != '\0')
    {
      if (p[count] != ',')
	{
	  f *= 10;
	  f += my_getnbr_char(p[count]);
	}
      count++;
      countdec++;
    }
  result = f;
  while (countdec != 0)
    {
      result /= 10;
      countdec--;
    }
  result += i;
  return (result);
}
