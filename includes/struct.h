/*
** struct.h for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Mar  8 17:47:16 2016 victor sousa
** Last update Mon Apr 25 05:55:52 2016 Ethan Kerdelhue
*/

#ifndef			STRUCT_H_
# define		STRUCT_H_

# include		"main.h"

typedef struct          s_point
{
  int  	           	x;
  int  	           	y;
  int  	           	z;
}                       t_point;

typedef struct          s_coord
{
  float                 x;
  float                 y;
  float                 z;
}                       t_coord;

typedef struct          s_pos
{
  int                   x;
  int                   y;
}                       t_pos;

typedef struct          s_sphere
{
  t_coord               center;
  int                   radius;
  char                  material;
}                       t_sphere;

typedef struct		s_triangle
{
  t_point		angle[3];
  char                  material;
}			t_triangle;

typedef struct		s_mat_list
{
  int			id;
  t_color		color;
  int			reflect;
  struct s_mat_list	*next;
}			t_mat_list;

typedef struct          s_light_list
{
  t_coord               center;
  int			intensity;
  struct s_light_list	*next;
}                       t_light_list;

typedef struct          s_obj_list
{
  char                  type;
  void                  *obj;
  struct s_obj_list     *next;
}                       t_obj_list;

typedef struct		s_ray
{
  t_coord		start;
  t_coord		dir;
}			t_ray;

typedef struct		s_raycast
{
  t_ray			ray;
  t_color               out_col;
  int                   depth;
  float                 coef;
  float                 dist;
  t_coord               dist_vector;
  t_obj_list            *obj_touch;
  t_mat_list            *mat_touch;
  t_coord               new_point;
  t_coord               normale;
  t_sphere              *sphere;
  t_light_list          *light_list;
  t_ray                 light_ray;
  int                   in_shadow;
  float                 lambert;
  float                 reflect;
}			t_raycast;

typedef struct          s_prog
{
  t_bunny_position      win_size;
  t_obj_list            *obj_list;
  t_mat_list		*mat_list;
  t_light_list		*light_list;
  t_bunny_window        *win;
  t_bunny_pixelarray    *pix;
  struct s_cmd		*cmd;
  char			**arg;
}                       t_prog;

#endif		      /*STRUCT_H*/
