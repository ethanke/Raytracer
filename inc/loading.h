/*
** loading.h for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 04:25:38 2016 victor sousa
** Last update Mon May 16 14:03:34 2016 Philippe Lefevre
*/

#ifndef			LOADING_H_
# define		LOADING_H_

# include		"main.h"

char			**load_scene_file(char *path, int i, int fd);
int			load_scene(t_prog *prog, char *scene_path);
int			load_obj_file(t_prog *prog, char *path);
t_vtx_list		*get_vertex(char **file);
t_coord			get_vertex_in_list(t_vtx_list *list, int id, int *flag);
t_obj_list		*parse_obj_formes(char **file, t_vtx_list *list);

int			load_light(t_prog *prog, char **file);
int			load_mat(t_prog *prog, char **file);
t_mat_list              *add_mat(t_mat_list *prev, char **file, int id);
int			load_obj(t_prog *prog, char **file);
t_obj_list		*add_sphere(t_obj_list *prev, char **file, int id);
t_obj_list              *add_triangle(t_obj_list *prev, char **file, int id);
t_obj_list              *add_plan(t_obj_list *prev, char **file, int id);
t_obj_list              *add_cone(t_obj_list *prev, char **file, int id);
t_obj_list              *add_cyl(t_obj_list *prev, char **file, int id);
t_obj_list              *add_pill(t_obj_list *prev, char **file, int id);
t_obj_list              *add_cube(t_obj_list *prev, char **file, int id);
int			waiting_screen(t_prog *prog);
int			get_cam_pos(char **file, t_prog *prog);
int			get_cam_look_at(char **file, t_prog *prog);
t_light_list		*add_empty_light(t_light_list *prev);
t_light_list		*add_empty_light2(t_light_list *prev);
t_light_list		*add_empty_light3(t_light_list *prev);
t_light_list		*add_empty_light4(t_light_list *prev);
t_mat_list              *add_empty_mat(t_mat_list *prev);
int			create_pix(t_prog *prog);
int			create_win(t_prog *prog);

#endif		      /*LOADING_H*/
