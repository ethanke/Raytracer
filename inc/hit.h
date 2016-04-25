/*
** hit.h for raytracer in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Mar  8 23:17:13 2016 victor sousa
** Last update Mon Apr 25 04:36:52 2016 Victor Sousa
*/

#ifndef			HIT_H_
# define		HIT_H_

# include		"main.h"

int                     hit_sphere(t_ray *r, t_sphere *s, float *t);
int			hit_triangle(t_ray *r, t_triangle *t, float *old_dist);
t_mat_list		*get_sphere_color(int mat_id, t_mat_list *mat);

t_obj_list		*hit(t_obj_list *obj_list, t_ray *ray, float *dist);

#endif		      /*HIT_H*/
