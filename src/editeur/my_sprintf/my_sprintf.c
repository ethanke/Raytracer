/*
** my_printf.c for my_printf in /home/leandr_g/rendu/Novembre_2015/PSU_2015_my_printf
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.net>
**
** Started on  Thu Nov 12 12:27:44 2015 Gaëtan Léandre
** Last update Wed May  4 04:19:19 2016 Gaëtan Léandre
*/

#include 		"main.h"

static t_sfonct		*init_sstruct(t_sfonct *tab)
{
  if ((tab = malloc(12 * sizeof(t_sfonct))) == NULL)
    return (NULL);
  tab[0].flag = 'c';
  (tab[0].f) = va_my_putchar_s;
  tab[1].flag = 's';
  (tab[1].f) = va_my_putstr_s;
  tab[2].flag = 'i';
  (tab[2].f) = va_my_putnbr_s;
  tab[3].flag = 'd';
  (tab[3].f) = va_my_putnbr_s;
  tab[4].flag = 'u';
  (tab[4].f) = va_my_putunbr_s;
  tab[5].flag = 'o';
  (tab[5].f) = va_my_octal_s;
  tab[6].flag = 'x';
  (tab[6].f) = va_my_examin_s;
  tab[7].flag = 'X';
  (tab[7].f) = va_my_examaj_s;
  tab[8].flag = 'b';
  (tab[8].f) = va_my_bin_s;
  tab[9].flag = 'S';
  (tab[9].f) = va_my_disp_unp_s;
  tab[10].flag = 'p';
  (tab[10].f) = va_my_adress_s;
  tab[11].flag = 'f';
  (tab[11].f) = va_my_putfnbr_s;
  return (tab);
}

static int			chose_ffunction(char c, t_sfonct *tab)
{
  int			i;

  i = 0;
  while (i < 12)
    {
      if (c == tab[i].flag)
	return (i);
      i++;
    }
  if (c == '\0')
    return (-2);
  return (-1);
}

static char			*print_ffct(va_list ap, t_sfonct *tab,
					   char *str, int *i)
{
  int			fct;
  int			wait;
  char			*result;

  if ((result = malloc_and_init()) == NULL)
    return (NULL);
  (*i)++;
  wait = str[*i] == ' ' ? 1 : 0;
  while (str[*i] == ' ')
    (*i)++;
  fct = chose_ffunction(str[*i], tab);
  if (fct == -1)
    {
      result = my_strcatchar(result, '%');
      if (str[*i] != '%')
	{
	  if (wait == 1)
	    result = my_strcatchar(result, ' ');
	  result = my_strcatchar(result, str[*i]);
	}
    }
  else if (fct > -1)
    {
      if (wait == 1)
	result = my_strcatchar(result, ' ');
      result = my_strcatprint(result, tab[fct].f(ap));
    }
  return (result);
}

char			*my_sprintf(char *str, ...)
{
  va_list		ap;
  t_sfonct		*tab;
  int	 		i;
  char			*result;

  tab = NULL;
  tab = init_sstruct(tab);
  if ((result = malloc_and_init()) == NULL)
    return (NULL);
  str[0] = '\0';
  i = 0;
  if (str == NULL || tab == NULL)
    return (NULL);
  va_start(ap, str);
  while (i < my_strlen(str))
    {
      if (str[i] == '%')
	result = my_strcatprint(result, print_ffct(ap, tab, str, &i));
      else
	result = my_strcatchar(result, str[i]);
      i++;
    }
  va_end(ap);
  free(tab);
  return (result);
}
