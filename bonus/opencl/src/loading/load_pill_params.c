/*
** load_cone_params.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/loading/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri Apr 29 05:54:30 2016 Victor Sousa
** Last update Mon May 16 10:56:49 2016 Philippe Lefevre
*/

#include		"main.h"

static int		get_center(t_cylin *p, char **file, int id)
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
  p->center.x = my_getnbr(get);
  free(get);
  lf[30] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  p->center.y = my_getnbr(get);
  free(get);
  lf[30] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  p->center.z = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_dir(t_cylin *p, char **file, int id)
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
  p->dir.x = my_getnbr(get);
  free(get);
  lf[27] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  p->dir.y = my_getnbr(get);
  free(get);
  lf[27] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  p->dir.z = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_radius(t_cylin *p, char **file, int id)
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
  p->radius = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_mat_id(t_cylin *p, char **file, int id)
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
  p->material = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_cone_height(t_cylin *p, char **file, int id)
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
  p->height = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

t_obj_list              *add_pill(t_obj_list *prev, char **file, int id)
{
  t_obj_list            *new;
  t_pill             	*p;

  if ((new = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((p = malloc(sizeof(t_pill))) == NULL)
    return (NULL);
  if ((p->cylin = malloc(sizeof(t_cylin))) == NULL)
    return (NULL);
  if (get_center(p->cylin, file, id) != 0)
    return (NULL);
  if (get_dir(p->cylin, file, id) != 0)
    return (NULL);
  if (get_radius(p->cylin, file, id) != 0)
    return (NULL);
  if (get_mat_id(p->cylin, file, id) != 0)
    return (NULL);
  if (get_cone_height(p->cylin, file, id) != 0)
    return (NULL);
  if ((p->cap[0] = malloc(sizeof(t_sphere))) == NULL)
    return (NULL);
  p->cap[0]->center = minus_vector(p->cylin->center,
				   float_time_vector((float)p->cylin->height
						     / 2.0, p->cylin->dir));
  p->cap[0]->material = p->cylin->material;
  p->cap[0]->material2 = p->cylin->material;
  p->cap[0]->radius = p->cylin->radius;
  if ((p->cap[1] = malloc(sizeof(t_sphere))) == NULL)
    return (NULL);
  p->cap[1]->center = add_vector(p->cylin->center,
				 float_time_vector((float)p->cylin->height
						   / 2.0, p->cylin->dir));
  p->cap[1]->material = p->cylin->material;
  p->cap[1]->material2 = p->cylin->material;
  p->cap[1]->radius = p->cylin->radius;
  p->cylin->center = minus_vector(p->cylin->center,
				  float_time_vector((float)p->cylin->height
						    / 2.0 , p->cylin->dir));
  new->obj = p;
  new->type = 'l';
  new->next = prev;
  return (new);
}
