/*
** struct.h for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/inc/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Tue Apr 26 01:10:14 2016 Ethan Kerdelhue
** Last update Wed Apr 27 18:14:07 2016 Victor Sousa
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

typedef struct		s_vtx_list
{
  t_coord		vtx;
  struct s_vtx_list	*next;
}			t_vtx_list;

typedef struct		s_plan
{
  t_coord		center;
  t_coord		dir;
  char                  material;
}			t_plan;

typedef struct		s_triangle
{
  t_coord		angle[3];
  char                  material;
}			t_triangle;

typedef struct		s_square
{
  t_coord		angle[4];
  char                  material;
}			t_square;

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
  t_triangle		*triangle;
  t_light_list          *light_list;
  t_ray                 light_ray;
  int                   in_shadow;
  float                 lambert;
  float                 reflect;
}			t_raycast;

typedef struct 		s_editor
{
  char			**arg;
  struct s_cmd		*cmd;
  int			fd;
}			t_editor;

typedef struct          s_prog
{
  t_bunny_position      win_size;
  t_point		cam_pos;
  t_bunny_position	cam_fov;
  t_obj_list            *obj_list;
  t_mat_list		*mat_list;
  t_light_list		*light_list;
  t_bunny_window        *win;
  t_bunny_pixelarray    *pix;
  t_editor		*editor;
}                       t_prog;
typedef struct s_cmd
{
  char			*index;
  char			*desc;
  int 			(*ptr)(t_prog *);
}			t_cmd;

#endif		      /*STRUCT_H*/
