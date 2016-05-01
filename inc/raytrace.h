/*
** raytrace.h for raytracing in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 01:05:12 2016 victor sousa
** Last update Sun May  1 22:17:32 2016 Victor Sousa
*/

#ifndef			RAYTRACE_H_
# define		RAYTRACE_H_

# include		"main.h"

# define		MAX_DEPTH		10

int                     raytrace(t_prog *prog);
void                    process_shadow(t_prog *prog, t_raycast *rcast);
int                     process_light(t_prog *prog, t_raycast *rcast);
void                    process_reflect(t_raycast *rcast);
int                     reflect_loop(t_prog *prog, t_raycast *rcast);

/*OBJECT CALCULS*/
int			calc_normale(t_prog *prog, t_raycast *rcast, t_ray *ray, t_color *col);
void			calc_sphere_normale(t_prog *prog, t_raycast *rcast, t_ray *ray);
void			calc_triangle_normale(t_prog *prog, t_raycast *rcast, t_ray *ray);
void			calc_plan_normale(t_prog *prog, t_raycast *rcast, t_ray *ray);
void			calc_cone_normale(t_prog *prog, t_raycast *rcast, t_ray *ray);

#endif		      /*RAYTRACE_H*/
