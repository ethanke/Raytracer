/*
** load_cone_params.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/loading/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri Apr 29 05:54:30 2016 Victor Sousa
** Last update Tue May  3 10:12:42 2016 Victor Sousa
*/

#include		"main.h"

static int		get_center(t_cylin *c, char **file, int id)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:object_list:objX:center:x") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:center:x");
  lf[21] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->center.x = my_getnbr(get);
  free(get);
  lf[30] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->center.y = my_getnbr(get);
  free(get);
  lf[30] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->center.z = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_dir(t_cylin *c, char **file, int id)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:object_list:objX:dir:x") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:dir:x");
  lf[21] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->dir.x = my_getnbr(get);
  free(get);
  lf[27] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->dir.y = my_getnbr(get);
  free(get);
  lf[27] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->dir.z = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_radius(t_cylin *c, char **file, int id)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:object_list:objX:radius") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:radius");
  lf[21] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->radius = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_mat_id(t_cylin *c, char **file, int id)
{
  char			*lf;
  char			*get;

 if ((lf = malloc(sizeof(char) *
		  my_strlen("scene:object_list:objX:material_id") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:material_id");
  lf[21] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->material = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_cone_height(t_cylin *c, char **file, int id)
{
  char			*lf;
  char			*get;

 if ((lf = malloc(sizeof(char) *
		  my_strlen("scene:object_list:objX:height") + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:height");
  lf[21] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  c->height = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

t_obj_list              *add_cyl(t_obj_list *prev, char **file, int id)
{
  t_obj_list            *new;
  t_obj_list            *new_base_bot;
  t_obj_list            *new_base_top;
  t_cylin             	*c;
  t_circle		*base_bot;
  t_circle		*base_top;

  if ((new = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((c = malloc(sizeof(t_cylin))) == NULL)
    return (NULL);
  if (get_center(c, file, id) != 0)
    return (NULL);
  if (get_dir(c, file, id) != 0)
    return (NULL);
  if (get_radius(c, file, id) != 0)
    return (NULL);
  if (get_mat_id(c, file, id) != 0)
    return (NULL);
  if (get_cone_height(c, file, id) != 0)
    return (NULL);
  new->obj = c;
  new->type = 'y';
  new->next = prev;
  if ((new_base_bot = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((base_bot = malloc(sizeof(t_circle))) == NULL)
    return (NULL);
  base_bot->plan.center.x = c->center.x;
  base_bot->plan.center.y = c->center.y;
  base_bot->plan.center.z = c->center.z;
  base_bot->plan.dir.x = -c->dir.x;
  base_bot->plan.dir.y = -c->dir.y;
  base_bot->plan.dir.z = -c->dir.z;
  base_bot->material = c->material;
  base_bot->radius = c->radius;
  new_base_bot->obj = base_bot;
  new_base_bot->type = 'i';
  new_base_bot->next = new;
  if ((new_base_top = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((base_top = malloc(sizeof(t_circle))) == NULL)
    return (NULL);
  base_top->plan.center = add_vector(c->center, float_time_vector(c->height , c->dir));
  base_top->plan.dir.x = c->dir.x;
  base_top->plan.dir.y = c->dir.y;
  base_top->plan.dir.z = c->dir.z;
  base_top->material = c->material;
  base_top->radius = c->radius;
  new_base_top->obj = base_top;
  new_base_top->type = 'i';
  new_base_top->next = new_base_bot;
  return (new_base_top);
}
