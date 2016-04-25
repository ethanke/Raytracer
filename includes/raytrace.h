/*
** raytrace.h for raytracing in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Fri Mar 11 01:05:12 2016 victor sousa
** Last update Mon Apr 25 06:15:11 2016 Victor Sousa
*/

#ifndef			RAYTRACE_H_
# define		RAYTRACE_H_

# include		"main.h"

int                     raytrace(t_prog *prog);
void                    process_shadow(t_prog *prog, t_raycast *rcast);
int                     process_light(t_prog *prog, t_raycast *rcast);
void                    process_reflect(t_raycast *rcast);
int                     reflect_loop(t_prog *prog, t_raycast *rcast);

/*OBJECT CALCULS*/
void			calc_sphere_normale(t_prog *prog, t_raycast *rcast);
void			calc_triangle_normale(t_prog *prog, t_raycast *rcast);

#endif		      /*RAYTRACE_H*/
