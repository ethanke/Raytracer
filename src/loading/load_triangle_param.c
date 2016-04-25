/*
** load_sphere.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Thu Mar 10 23:13:22 2016 victor sousa
** Last update Mon Apr 25 03:58:04 2016 victor sousa
*/

#include	"main.h"

/*
static int		get_center(t_triangle *t, char **file, int id)
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
  t->center.x = my_getnbr(get);
  free(get);
  lf[30] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  t->center.y = my_getnbr(get);
  free(get);
  lf[30] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  t->center.z = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}
*/
/*
static int		get_radius(t_triangle *t, char **file, int id)
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
  t->radius = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}
*/

static int		get_mat_id(t_triangle *t, char **file, int id)
{
  char			*lf;
  char			*get;

 if ((lf = malloc(sizeof(char) *
		  my_strlen("scene:object_list:objX:material_id")
		  + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:material_id");
  lf[21] = id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  t->material = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_point(t_triangle *t, char **file, int id, int p_id)
{
  char			*lf;
  char			*get;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:object_list:objX:pX:x")
		   + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:pX:x");
  lf[21] = id + 49;
  lf[24] = p_id + 49;
  printf("%s\n", lf);
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  t->angle[p_id].x = my_getnbr(get);
  free(get);
  lf[27] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  t->angle[p_id].y = my_getnbr(get);
  free(get);
  lf[27] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  t->angle[p_id].z = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

t_obj_list              *add_triangle(t_obj_list *prev, char **file, int id)
{
  t_obj_list            *new;
  t_triangle            *t;
  int			pointi;

  printf("found triangle\n");
  if ((new = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((t = malloc(sizeof(t_triangle))) == NULL)
    return (NULL);
  pointi = 0;
  while (pointi < 3)
    {
      if (get_point(t, file, id, pointi) != 0)
	return (NULL);
      printf("point %d,\tx:%d\ty:%d\tz:%d\n", pointi + 1,
	     t->angle[pointi].x, t->angle[pointi].y, t->angle[pointi].z);
      pointi++;
    }
  if (get_mat_id(t, file, id) != 0)
    return (NULL);
  new->obj = t;
  new->type = 't';
  new->next = prev;
  return (new);
}
