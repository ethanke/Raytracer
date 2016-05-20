/*
** my_disp_unprintable.c for my_printf in /home/leandr_g/rendu/Novembre_2015/PSU_2015_my_printf
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.net>
**
** Started on  Thu Nov 12 14:59:18 2015 Gaëtan Léandre
** Last update Fri May 20 03:41:13 2016 Gaëtan Léandre
*/

#include "client.h"

void	disp_unprintable_in(int fd, char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] < 32 || str[i] > 126)
	{
	  my_putchar_in(fd, '\\');
	  my_putnbr_base_in(fd, str[i], "01234567", 2);
	}
      else
	my_putchar_in(fd, str[i]);
      i++;
    }
}
