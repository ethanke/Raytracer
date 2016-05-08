/*
** read_opti.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/utils/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sun May  8 09:44:34 2016 Gaëtan Léandre
** Last update Sun May  8 09:55:16 2016 Gaëtan Léandre
*/

#include		"main.h"

char			*read_opti(char *file)
{
  struct stat		st;
  int			fd;
  char			*str;
  int			size;

  if ((fd = open(file, O_RDONLY)) < 0 || stat(file, &st) == -1)
    return (NULL);
  size = st.st_size;
  if ((str = malloc(size + 1)) == NULL)
    return (NULL);
  size = read(fd, str, size);
  if (size < 0)
    return (NULL);
  str[size] = '\0';
  return (str);
}
