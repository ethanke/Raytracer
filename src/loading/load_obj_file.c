/*
** load_obj_file.c for  in /home/sousa_v/rendu/lapin/raytracer_temp/src/loading/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Mon Apr 25 08:37:20 2016 Victor Sousa
** Last update Tue Apr 26 01:21:27 2016 Gaëtan Léandre
*/

#include		"main.h"

static t_light_list	*add_empty_light(t_light_list *prev)
{
  t_light_list          *new;

  if ((new = malloc(sizeof(t_light_list))) == NULL)
    return (NULL);
  new->center.x = 0;
  new->center.y = 100;
  new->center.z = -1000;
  new->intensity = 75;
  new->next = prev;
  return (new);
}

t_mat_list              *add_empty_mat(t_mat_list *prev)
{
  t_mat_list            *new;

  if ((new = malloc(sizeof(t_mat_list))) == NULL)
    return (NULL);
  new->color.full = 0xFFFFFA00;
  new->id = 1;
  new->next = prev;
  return (new);
}

t_obj_list              *add_fake_triangle(t_obj_list *prev)
{
  t_obj_list            *new;
  t_triangle            *t;

  if ((new = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((t = malloc(sizeof(t_triangle))) == NULL)
    return (NULL);
  t->angle[0].x = 100; t->angle[0].y = 100; t->angle[0].z = 100;
  t->angle[1].x = 300; t->angle[1].y = 100; t->angle[1].z = 100;
  t->angle[2].x = 100; t->angle[2].y = 300; t->angle[2].z = 100;
  t->material = 1;
  new->obj = t;
  new->type = 't';
  new->next = prev;
  return (new);
}

int			load_obj_file(t_prog *prog, char *path)
{
  char			**file;
  t_vtx_list		*vtx_list;

  prog->win_size.x = 1080;
  prog->win_size.y = 720;
  prog->cam_pos.x = 320;
  prog->cam_pos.y = 240;
  prog->cam_pos.z = -1000;
  if ((file = load_scene_file(path)) == NULL)
    return (-1);
  prog->light_list = NULL;
  if ((prog->light_list = add_empty_light(prog->light_list)) == NULL)
    return (-1);
  prog->mat_list = NULL;
  if ((prog->mat_list = add_empty_mat(prog->mat_list)) == NULL)
    return (-1);
  if ((vtx_list = get_vertex(file)) == NULL)
    return (-1);
  if ((prog->obj_list = parse_obj_formes(file, vtx_list)) == NULL)
    return (-1);
  return (0);
}
