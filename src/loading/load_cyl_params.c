/*
** load_cone_params.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/loading/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri Apr 29 05:54:30 2016 Victor Sousa
** Last update Wed May  4 22:51:20 2016 Victor Sousa
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
  t_cylin             	*c;

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
  if ((c->cap[0] = malloc(sizeof(t_circle))) == NULL)
    return (NULL);
  c->cap[0]->plan.center = minus_vector(c->center, float_time_vector((float)c->height / 2.0, c->dir));
  c->cap[0]->plan.dir.x = c->dir.x;
  c->cap[0]->plan.dir.y = c->dir.y;
  c->cap[0]->plan.dir.z = c->dir.z;
  c->cap[0]->material = c->material;
  c->cap[0]->radius = c->radius;
  if ((c->cap[1] = malloc(sizeof(t_circle))) == NULL)
    return (NULL);
  c->cap[1]->plan.center = add_vector(c->center, float_time_vector((float)c->height / 2.0, c->dir));
  c->cap[1]->plan.dir.x = c->dir.x;
  c->cap[1]->plan.dir.y = c->dir.y;
  c->cap[1]->plan.dir.z = c->dir.z;
  c->cap[1]->material = c->material;
  c->cap[1]->radius = c->radius;
  c->center = minus_vector(c->center, float_time_vector(c->height / 2.0 , c->dir));
  new->obj = c;
  new->type = 'y';
  new->next = prev;
  return (new);
}
