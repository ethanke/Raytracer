/*
** raytrace.h for raytracing in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 01:05:12 2016 victor sousa
** Last update Wed May  4 00:29:40 2016 Victor Sousa
*/

#ifndef			RAYTRACE_H_
# define		RAYTRACE_H_

# include		"main.h"

# define		MAX_DEPTH		10
#define			SIZE_TILE		75

int                     raytrace(t_prog *prog);
t_color			raytrace_loop(t_prog *prog,
				      t_raycast *rcast,
				      t_bunny_position pos);
void                    process_shadow(t_prog *prog, t_raycast *rcast);
int                     process_light(t_prog *prog, t_raycast *rcast);
void                    process_reflect(t_raycast *rcast);
int                     reflect_loop(t_prog *prog, t_raycast *rcast);

/*OBJECT CALCULS*/
int			calc_normale(t_prog *prog, t_raycast *rcast);
void			calc_sphere_normale(t_prog *prog, t_raycast *rcast);
void			calc_triangle_normale(t_prog *prog, t_raycast *rcast);
void			calc_plan_normale(t_prog *prog, t_raycast *rcast);
void			calc_cone_normale(t_prog *prog, t_raycast *rcast);
void			calc_cyl_normale(t_prog *prog, t_raycast *rcast);
void			calc_circle_normale(t_prog *prog, t_raycast *rcast);

#endif		      /*RAYTRACE_H*/
