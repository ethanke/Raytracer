/*
** loading.h for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Tue Feb  9 04:25:38 2016 victor sousa
** Last update Fri Mar 11 00:00:18 2016 victor sousa
*/

#ifndef			LOADING_H_
# define		LOADING_H_

# include		"main.h"

int			load_scene(t_prog *prog, char *scene_path);

int			load_light(t_prog *prog, char **file);
int			load_mat(t_prog *prog, char **file);
t_mat_list              *add_mat(t_mat_list *prev, char **file, int id);
int			load_obj(t_prog *prog, char **file);
t_obj_list		*add_sphere(t_obj_list *prev, char **file, int id);

#endif		      /*LOADING_H*/
