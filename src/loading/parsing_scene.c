/*
** parsing_scene.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 04:25:03 2016 victor sousa
** Last update Sun May  1 21:45:14 2016 Victor Sousa
*/

#include		"main.h"

t_line_list		*add_line_list(t_line_list *head, char *str)
{
  t_line_list		*new;
  t_line_list		*tmp;

  if ((new = malloc(sizeof(t_line_list))) == NULL)
    return (NULL);
  new->str = str;
  new->next = NULL;
  if (head == NULL)
    return new;
  else
    {
      tmp = head;
      while(tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
      return (head);
    }
}

int			list_len(t_line_list *list)
{
  int			i;
  t_line_list		*tmp;

  i = 0;
  tmp = list;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

char			**my_list_to_wordtab(t_line_list *list)
{
  char			**out;
  t_line_list		*tmp;
  int			i;

  if ((out = malloc(sizeof(char *) * (list_len(list) + 1))) == NULL)
    return (NULL);
  tmp = list;
  i = 0;
  while (tmp != NULL)
    {
      out[i] = tmp->str;
      tmp = tmp->next;
      i++;
    }
  out[i] = '\0';
  return (out);
}

char			**load_scene_file(char *path)
{
  int			fd;
  char			*str;
  char			**file;
  int			i;
  t_line_list		*file_list;

  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  file_list = NULL;
  while ((str = get_next_line(fd)) != NULL)
    file_list = add_line_list(file_list, str);
  if ((file = my_list_to_wordtab(file_list)) == NULL)
    return (NULL);
  i = 0;
  while (file[i])
    {
      if ((file[i] = epur_str(file[i], " \t\n")) == NULL)
	return (NULL);
      i++;
    }
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

static int		get_cam_look_at(char **file, t_prog *prog)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:view:look_at:x")
		   + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:view:look_at:x");
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  prog->look_at.x = my_getnbr(get);
  free(get);
  lf[19] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  prog->look_at.y = my_getnbr(get);
  free(get);
  lf[19] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  prog->look_at.z = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

int			load_scene(t_prog *prog, char *scene_path)
{
  char			**file;
  char			*get;
  t_coord		dir;

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
  if ((get = get_field(file, "scene:view:fov")) == NULL)
    return (-1);
  prog->cam_fov.x = my_getnbr(get);
  free(get);
  if ((get = get_field(file, "scene:view:background")) == NULL)
    return (-1);
  if (my_strcmp(get, "NULL") == 0)
    {
      if ((prog->background = create_text_uni(prog->win_size.x, prog->win_size.x, 0xff000000)) == NULL)
	return (-1);
    }
  else
    {
      if ((prog->background = load_image(get)) == NULL)
	return (-1);
      place_into_hitbox(prog->background, prog->background,
			create_hitbox(0, 0, prog->win_size.x, prog->win_size.y));
    }
  free(get);
  prog->cam_fov.y = prog->cam_fov.x * ((prog->win_size.x / prog->win_size.y) / 1.5);
  if (get_cam_pos(file, prog) == 1 ||
      get_cam_look_at(file, prog) == 1 ||
      load_mat(prog, file) == -1 ||
      load_light(prog, file) == -1 ||
      load_obj(prog, file) == -1)
    return (-1);
  if (prog->look_at.x == prog->cam_pos.x &&
      prog->look_at.y == prog->cam_pos.y &&
      prog->look_at.z == prog->cam_pos.z)
    {
      my_putstr("Wrong camera placement\n");
      return (-1);
    }
  dir = normalize(minus_point(prog->look_at, prog->cam_pos));
  prog->cam_rot.x = RTD(acos(-(dir.z / sqrt(pow(dir.x, 2) + pow(dir.z, 2))))) - 90;
  prog->cam_rot.y = RTD((M_PI / 2 - acos(dir.y)));
  prog->cam_dir = normalize(minus_point(prog->look_at, prog->cam_pos));
  return (0);
}
