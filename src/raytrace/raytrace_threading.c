/*
** raytrace_threading.c for Raytracer in /home/lefevr_h/Workspace/Github/Raytracer/src/raytrace/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Sun May  8 02:20:22 2016 Philippe Lefevre
** Last update Thu May 12 12:44:11 2016 Philippe Lefevre
*/

#include		"main.h"
pthread_mutex_t		mutex = PTHREAD_MUTEX_INITIALIZER;

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
  if (prog->verbose)
    my_printf(1, "Thread number %d : %d to %d\n", prog->thread_id, pos.x, end);
  while (++pos.x < end)
    {
      pos.y = -1;
      while (++pos.y < prog->win_size.y)
	{
	  pthread_mutex_lock(&mutex);
	  pixel_color.full = calcul_pixel(prog, raycast, pos);
	  pthread_mutex_unlock(&mutex);
	  tekpixel(prog->pix, &pos, &pixel_color);
	}
    }
  prog->rendu_success -= (prog->thread_id + 1);
  pthread_exit(NULL);
}
int			raytrace_thread_create(t_prog *prog, int i,
					       pthread_t thread_id[])
{
  time_t		time_thread;

  prog->thread_id = i;
  if (pthread_create(&thread_id[i], NULL, raytrace_zone, (void *)prog))
    return (my_printf(2, "Error: can not create thread\n") - 1);
  time_thread = time(NULL);
  while (time_thread == time(NULL));
  return (0);
}

int			raytrace_threading(t_prog *prog)
{
  pthread_t		thread_id[prog->thread_nb];
  time_t		time_beg;
  time_t		time_end;
  t_bunny_position      pos;
  int			i;

  pos.x = 0;
  pos.y = 0;
  i = -1;
  if (prog->verbose)
    my_putstr("\nRaytracing multi-threading started\n");
  i = -1;
  time_beg = time(NULL);
  my_putstr("\nStarting create thread\n");
  prog->rendu_success = 0;
  while (++i < prog->thread_nb)
    if (raytrace_thread_create(prog, i, thread_id))
	return (-1);
  my_putstr("Thread create successfull\n");
  i = -1;
  while (prog->display_rendu && (prog->rendu_success > 0))
    {
      bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
      bunny_display(prog->win);
    }
  while (++i < prog->thread_nb)
    pthread_join(thread_id[i], NULL);
  time_end = time(NULL);
  my_printf(1, "\nRendu en %d heures %d minutes %d secondes\n", (time_end - time_beg) / 3600,
	    ((time_end - time_beg) % 3600) / 60, ((time_end - time_beg) % 3600) % 60);
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
  bunny_display(prog->win);
  my_putstr("Raytracing multi-threading successfull\n");
  return (0);
}
