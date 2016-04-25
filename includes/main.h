/*
** main.h for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 01:45:54 2016 victor sousa
** Last update Mon Apr 25 05:02:12 2016 Ethan Kerdelhue
*/

#ifndef			MAIN_H_
# define		MAIN_H_

# include		<unistd.h>
# include               <math.h>
# include               <sys/types.h>
# include               <sys/stat.h>
# include               <fcntl.h>

# include		"lapin.h"
# include		"struct.h"
# include		"output.h"
# include		"raytrace.h"
# include		"hit.h"
# include		"loading.h"
# include		"utils.h"
# include		"editor.h"
# include		"get_next_line.h"
# include		"xml.h"

# define		Deg_To_Rad(ang)	((ang) / 180.0 * M_PI)
# define		ABS(x)		((x)<0 ? -(x) : (x))

t_bunny_response	mainloop(void *p);
void			free_stuff(t_prog *prog);

#endif		      /*MAIN_H*/
