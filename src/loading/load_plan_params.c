/*
** load_plan_params.c for  in /home/sousa_v/rendu/lapin/raytracer_tmp/src/loading/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Wed Apr 27 17:06:03 2016 Victor Sousa
** Last update Wed Apr 27 17:07:12 2016 Victor Sousa
*/

#include		"main.h"

static int		get_mat_id(t_plan *p, char **file, int id)
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
  p->material = my_getnbr(get);
  free(get);
  free(lf);
  return (0);
}

static int		get_point(t_plan *p, char **file, int id, int p_id)
{
  char			*lf;
  char			*get;
  t_point		tmp;

  if ((lf = malloc(sizeof(char) *
		   my_strlen("scene:object_list:objX:pX:x")
		   + 1)) == NULL)
    return (1);
  lf[0] = '\0';
  lf = my_strcat(lf, "scene:object_list:objX:pX:x");
  lf[21] = id + 49;
  lf[24] = p_id + 49;
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  tmp.x = my_getnbr(get);
  free(get);
  lf[26] = 'y';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  tmp.y = my_getnbr(get);
  free(get);
  lf[26] = 'z';
  if ((get = get_field(file, lf)) == NULL)
    return (1);
  tmp.z = my_getnbr(get);
  free(get);
  free(lf);
  p->angle[p_id].x = tmp.x;
  p->angle[p_id].y = tmp.y;
  p->angle[p_id].z = tmp.z;
  return (0);
}

t_obj_list              *add_plan(t_obj_list *prev, char **file, int id)
{
  t_obj_list            *new;
  t_plan           	*p;
  int			pointi;

  if ((new = malloc(sizeof(t_obj_list))) == NULL)
    return (NULL);
  if ((p = malloc(sizeof(t_plan))) == NULL)
    return (NULL);
  pointi = 0;
  while (pointi < 3)
    {
      if (get_point(p, file, id, pointi) != 0)
	return (NULL);
      pointi++;
    }
  if (get_mat_id(p, file, id) != 0)
    return (NULL);
  new->obj = p;
  new->type = 'p';
  new->next = prev;
  return (new);
}
