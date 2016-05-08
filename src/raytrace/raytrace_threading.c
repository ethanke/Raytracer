/*
** raytrace_threading.c for Raytracer in /home/lefevr_h/Workspace/Github/Raytracer/src/raytrace/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Sun May  8 02:20:22 2016 Philippe Lefevre
** Last update Sun May  8 05:27:50 2016 Philippe Lefevre
*/

#include		"main.h"

void			*raytrace_zone(void *p)
{
  t_prog		*prog;
  t_raycast		raycast;
  t_bunny_position      pos;
  t_color		pixel_color;
  int			end;

  prog = p;
  raycast.touch_circle = 0;
  pos.x = ((prog->win_size.x / prog->thread_nb) * prog->thread_id) - 1;
  end = ((prog->win_size.x / prog->thread_nb) * (prog->thread_id + 1));
  my_printf(1, "Thread number %d : %d to %d\n", prog->thread_id, pos.x, end);
  while (++pos.x < end)
    {
      pos.y = -1;
      while (++pos.y < prog->win_size.y)
	{
	  pixel_color.full = calcul_pixel(prog, raycast, pos);
	  tekpixel(prog->pix, &pos, &pixel_color);
	}
    }
  pthread_exit(NULL);
}

int			raytrace_threading(t_prog *prog)
{
  t_bunny_position      pos;
  pthread_t		thread_id[prog->thread_nb];
  int			i;
  time_t		mytime;

  pos.x = 0;
  pos.y = 0;
  my_putstr("\nRaytracing multi-threading started\n");
  i = -1;
  while (++i < prog->thread_nb)
    {
      prog->thread_id = i;
      pthread_create(&thread_id[i], NULL, raytrace_zone, (void *)prog);
      mytime = time(NULL);
      while (mytime == time(NULL));
    }
  i = -1;
  while (++i < prog->thread_nb)
    pthread_join(thread_id[i], NULL);
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
  bunny_display(prog->win);
  my_putstr("Raytracing multi-threading successfull\n");
  return (0);
}
