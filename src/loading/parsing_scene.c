/*
** parsing_scene.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 04:25:03 2016 victor sousa
** Last update Tue Apr 26 00:01:36 2016 Victor Sousa
*/

#include		"main.h"

#define			READ_LENGHT	4096

char			**load_scene_file(char *path)
{
  int			fd;
  char			*str;
  char			*file1d;
  int			i;
  char			**file;

  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((file1d = malloc(READ_LENGHT + 1)) == NULL)
    return (NULL);
  if ((str = malloc(READ_LENGHT + 1)) == NULL)
    return (NULL);
  file1d[0] = '\0';
  i = 0;
  while (read(fd, str, 4096) > 0)
    {
      str[4096] = '\0';
      file1d = my_strcat(file1d, str);
      if ((file1d = my_realloc(file1d, my_strlen(file1d) + READ_LENGHT + 1)) == NULL)
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

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:view:cam_pos:x")
		   + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:view:cam_pos:x");
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  prog->cam_pos.x = my_getnbr(get);
  free(get);
  lf[19] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  prog->cam_pos.y = my_getnbr(get);
  free(get);
  lf[19] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  prog->cam_pos.z = my_getnbr(get);
  free(get);
  free(lf);
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
  prog->cam_fov.x = 75;
  prog->cam_fov.y = 50;
  if (get_cam_pos(file, prog) == 1 ||
      load_mat(prog, file) == -1 ||
      load_light(prog, file) == -1 ||
      load_obj(prog, file) == -1)
    return (-1);
  return (0);
}
