/*
** parsing_scene.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 04:25:03 2016 victor sousa
** Last update Mon Apr 25 23:47:14 2016 Victor Sousa
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
  i = 0;
  while (file[i])
    {
      if ((file[i] = epur_str(file[i], " \t\n")) == NULL)
	return (NULL);
      i++;
    }
  free(file1d);
  return (file);
}

static int		get_cam_pos(char **file, t_prog *prog)
{
  char			*lf;
  char			*get;
  t_point		tmp;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:view:cam_pos:x")
		   + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:view:cam_pos:x");
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  tmp.x = my_getnbr(get);
  free(get);
  lf[19] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  tmp.y = my_getnbr(get);
  free(get);
  lf[19] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  tmp.z = my_getnbr(get);
  free(get);
  free(lf);
  prog->cam_pos.x = tmp.x;
  prog->cam_pos.y = tmp.y;
  prog->cam_pos.z = tmp.z;
  return (0);
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
  if (get_cam_pos(file, prog))
    return (-1);
  printf("x:%d, y:%d, z:%d\n", prog->cam_pos.x, prog->cam_pos.y, prog->cam_pos.z);
  if (load_mat(prog, file) == -1 ||
      load_light(prog, file) == -1 ||
      load_obj(prog, file) == -1)
    return (-1);
  return (0);
}
