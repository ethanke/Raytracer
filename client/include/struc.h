/*
** struc.h for clinet in /Users/leandr_g/Documents/Shared folder/Raytracer/client/include/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Fri May 20 03:43:29 2016 Gaëtan Léandre
** Last update Fri May 20 03:53:04 2016 Gaëtan Léandre
*/

#ifndef			_STRUC_H_
# define		_STRUC_H_

#include		"client.h"

typedef union		u_color
{
  unsigned int		full;
  char			argb[4];
}			t_color;

typedef struct          s_texture
{
  int                   width;
  int                   height;
  t_color               **color;
}                       t_texture;

typedef struct          s_hitbox
{
  int                   x;
  int                   y;
  int                   width;
  int                   height;
}                       t_hitbox;

typedef struct		s_bunny_position
{
  int			x;
  int			y;
}			t_bunny_position;

typedef struct          s_cmyk
{
  float                 c;
  float                 m;
  float                 y;
  float                 k;
}                       t_cmyk;

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
  char                  material2;
}                       t_sphere;

typedef struct		s_plan
{
  t_coord		center;
  t_coord		dir;
  char                  material;
  char                  material2;
}			t_plan;

typedef struct		s_circle
{
  t_plan		plan;
  float			radius;
  char			material;
}			t_circle;

typedef struct		s_cube
{
  t_coord               center;
  t_coord               size;
  char			material;
}			t_cube;

typedef struct          s_cylin
{
  t_coord               center;
  t_coord               dir;
  int                   radius;
  int                   height;
  char                  material;
  t_circle		*cap[2];
}                       t_cylin;

typedef struct          s_pill
{
  t_cylin		*cylin;
  t_sphere		*cap[2];
}                       t_pill;

typedef struct		s_vtx_list
{
  t_coord		vtx;
  struct s_vtx_list	*next;
}			t_vtx_list;

typedef struct		s_cone
{
  t_coord		center;
  t_coord		dir;
  int			radius;
  int			height;
  char                  material;
  t_circle		*cap;
}			t_cone;

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
  t_texture		*texture;
  char			*texture_path;
  char			*mtl_name;
  float			bump;
  char			sky;
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
  t_cone		*cone;
  t_plan		*plan;
  t_cylin		*cyl;
  t_circle		*circle;
  t_light_list          *light_list;
  t_ray                 light_ray;
  int                   in_shadow;
  float                 lambert;
  float                 reflect;
  char			touch_circle;
}			t_raycast;

typedef struct 		s_editor
{
  char			**arg;
  struct s_cmd		*cmd;
  int			fd;
}			t_editor;

typedef struct          s_opt
{
  int			thread_nb;
  int			rendu_success;
  int			rendu_display;
  int			rendu_vertical;
  int			verbose;
  int			start;
  int			stop;
  char			cluster;
}			t_opt;

typedef struct          s_prog
{
  t_bunny_position      win_size;
  t_point		cam_pos;
  t_point		look_at;
  t_coord		cam_dir;
  t_bunny_position	cam_fov;
  t_bunny_position	cam_rot;
  t_obj_list            *obj_list;
  t_mat_list		*mat_list;
  t_light_list		*light_list;
  t_editor		*editor;
  t_texture		*background;
  char			*background_path;
  int			anti_alias;
  t_opt			*opt;
}                       t_prog;

#endif
