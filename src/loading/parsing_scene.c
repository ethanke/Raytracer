/*
** parsing_scene.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 04:25:03 2016 victor sousa
** Last update Mon Apr 25 02:57:54 2016 victor sousa
*/

#include		"main.h"

char			**load_scene_file(char *path)
{
  int			fd;
  char			c;
  char			*file1d;
  int			i;
  char			**file;

  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((file1d = malloc(sizeof(char) * 2)) == NULL)
    return (NULL);
  i = 0;
  while (read(fd, &c, 1) > 0)
    {
      file1d[i] = c;
      file1d[i + 1] = 0;
      if ((file1d = my_realloc(file1d, sizeof(char) *
			       (my_strlen(file1d) + 2))) == NULL)
	return (NULL);
      i++;
    }
  if ((file = my_str_to_wordtab(file1d, 0, 0)) == NULL)
    return (NULL);
  free(file1d);
  return (file);
}

int			load_scene(t_prog *prog, char *scene_path)
{
  char			**file;
  char			*get;

  if ((file = load_scene_file(scene_path)) == NULL)
    return (-1);
  if ((get = get_field(file, "scene:view:x_size")) == NULL)
    return (-1);
  prog->win_size.x = my_getnbr(get);
  free(get);
  if ((get = get_field(file, "scene:view:y_size")) == NULL)
    return (-1);
  prog->win_size.y = my_getnbr(get);
  free(get);
  if (load_mat(prog, file) == -1 ||
      load_light(prog, file) == -1 ||
      load_obj(prog, file) == -1)
    return (-1);
  return (0);
}
