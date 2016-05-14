/*
** client_raytrace.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/client/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Fri May 13 04:44:05 2016 Gaëtan Léandre
** Last update Sat May 14 09:41:05 2016 Gaëtan Léandre
*/

#include		"main.h"

int			load_scene_open(t_prog *prog, char *str)
{
  char			**file;
  char			*get;
  t_coord		dir;

  if ((file = str_to_wordtab(str, "\n")) == NULL)
    return (-1);
  if ((get = get_field(file, "scene:view:x_size")) == NULL)
    {
      my_putstr("Could not find scene:view:x_size\n");
      return (-1);
    }
  prog->win_size.x = my_getnbr(get);
  free(get);
  if ((get = get_field(file, "scene:view:y_size")) == NULL)
    {
      my_putstr("Could not find scene:view:y_size\n");
      return (-1);
    }
  prog->win_size.y = my_getnbr(get);
  free(get);
  if ((get = get_field(file, "scene:view:fov")) == NULL)
    {
      my_putstr("Could not find scene:view:fov\n");
      return (-1);
    }
  prog->cam_fov.x = my_getnbr(get);
  free(get);
  if ((get = get_field(file, "scene:view:alias")) == NULL)
    {
      my_putstr("Could not find scene:view:alias\n");
      return (-1);
    }
  prog->anti_alias = my_getnbr(get);
  free(get);
  if ((get = get_field(file, "scene:view:background")) == NULL)
    {
      my_putstr("Could not find scene:view:background\n");
      return (-1);
    }
  if ((prog->background_path = malloc(my_strlen(get) + 1)) == NULL)
    return (-1);
  prog->background_path[0] = '\0';
  prog->background_path = my_strcat(prog->background_path, get);
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
  free_tab(file);
  return (0);
}

int			load_obj_file_open(t_prog *prog, char *str)
{
  char			**file;
  t_vtx_list		*vtx_list;
  t_coord		dir;

  prog->win_size.x = 1080;
  prog->win_size.y = 720;
  prog->cam_pos.x = -500;
  prog->cam_pos.y = 125;
  prog->cam_pos.z = -500;
  prog->cam_fov.x = 90;
  prog->cam_fov.y = prog->cam_fov.x * ((prog->win_size.x / prog->win_size.y) / 1.5);
  prog->look_at.x = 0;
  prog->look_at.y = 0;
  prog->look_at.z = 0;
  dir = normalize(minus_point(prog->look_at, prog->cam_pos));
  prog->cam_rot.x = RTD(acos(-(dir.z / sqrt(pow(dir.x, 2) + pow(dir.z, 2))))) - 90;
  prog->cam_rot.y = RTD((M_PI / 2 - acos(dir.y)));
  prog->cam_dir = normalize(minus_point(prog->look_at, prog->cam_pos));
  if ((file = str_to_wordtab(str, "\n")) == NULL)
    return (-1);
  prog->light_list = NULL;
  if ((prog->light_list = add_empty_light(prog->light_list)) == NULL)
    return (-1);
  if ((prog->light_list = add_empty_light2(prog->light_list)) == NULL)
    return (-1);
  if ((prog->light_list = add_empty_light3(prog->light_list)) == NULL)
    return (-1);
  if ((prog->light_list = add_empty_light4(prog->light_list)) == NULL)
    return (-1);
  if ((prog->background = create_text_uni(prog->win_size.x, prog->win_size.x, 0xff000000)) == NULL)
    return (-1);
  prog->anti_alias = 1;
  prog->mat_list = NULL;
  if ((prog->mat_list = add_empty_mat(prog->mat_list)) == NULL)
    return (-1);
  if ((vtx_list = get_vertex(file)) == NULL)
    return (-1);
  if ((prog->obj_list = parse_obj_formes(file, vtx_list)) == NULL)
    return (-1);
  free_tab(file);
  return (0);
}

void			client_raytrace(char *str, int *status, SOCKET sock)
{
  char			buffer[BUF_SIZE];
  unsigned int		*grille;
  char			**tab;
  t_prog		prog;

  if (read_server(sock, buffer) == 0)
    {
      *status = -1;
      return;
    }
  tab = str_to_wordtab(buffer, " ");
  if ((tab[2][0] == 'x' && load_scene_open(&prog, str) == -1)
    || (tab[2][1] == 'o' && load_obj_file_open(&prog, str) == -1))
  {
    *status = -1;
    return;
  }
  prog.thread_nb = 4;
  grille = raytrace_threading_client(&prog, my_getnbr(tab[0]), my_getnbr(tab[1]));
  my_printf(1, "Envois des calculs\n");
  if (grille == NULL || send(sock, grille, sizeof(unsigned int) * (my_getnbr(tab[1]) - my_getnbr(tab[0])) * prog.win_size.y, 0) < 0)
    *status = -1;
  else
    {
      my_printf(1, "Caluls envoyés, en attente d'une autre information du serveur\n");
      *status = 0;
      free(grille);
    }
  free(str);
  free_tab(tab);
  *status = 0;
}
