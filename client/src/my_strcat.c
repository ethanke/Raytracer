/*
** my_strcat.c for strcat in /Users/leandr_g/Documents/Shared folder/Raytracer/client/src/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Fri May 20 04:05:28 2016 Gaëtan Léandre
** Last update Fri May 20 04:05:35 2016 Gaëtan Léandre
*/

char            *my_strcat(char *dest, char *src)
{
  int           len;
  int           i;

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
