/*
** raytrace_threading.c for Raytracer in /home/lefevr_h/Workspace/Github/Raytracer/src/raytrace/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Sun May  8 02:20:22 2016 Philippe Lefevre
** Last update Fri May 13 23:20:39 2016 Philippe Lefevre
*/

#include		"main.h"

void			*raytrace_verticale(void *p)
{
  static int		thread_id = -1;
  t_prog		*prog;
  t_raycast		raycast;
  t_bunny_position      pos;
  t_color		pixel_color;
  int			end;

  prog = p;
  raycast.touch_circle = 0;
  pos.x = ((prog->win_size.x / prog->thread_nb) * ++thread_id) - 1;
  end = ((prog->win_size.x / prog->thread_nb) * (thread_id + 1));
  if (prog->verbose)
    my_printf(1, "Thread number %d : %d to %d\n", thread_id, pos.x, end);
  while (++pos.x < end)
    {
      pos.y = (prog->win_size.y / prog->all_client * (prog->nb_client - 1)) - 1;
      while (++pos.y < (prog->win_size.y / prog->all_client * prog->nb_client))
	{
	  pixel_color.full = calcul_pixel(prog, raycast, pos);
	  tekpixel(prog->pix, &pos, &pixel_color);
	}
    }
  prog->rendu_success -= (thread_id + 1);
  pthread_exit(NULL);
}

void			*raytrace_horizontale(void *p)
{
  static int		thread_id = -1;
  t_prog		*prog;
  t_raycast		raycast;
  t_bunny_position      pos;
  t_color		pixel_color;
  int			end;

  prog = p;
  raycast.touch_circle = 0;
  pos.y = ((prog->win_size.y / prog->thread_nb) * ++thread_id) - 1;
  end = ((prog->win_size.y / prog->thread_nb) * (thread_id + 1));
  if (prog->verbose)
    my_printf(1, "Thread number %d : %d to %d\n", thread_id, pos.y, end);
  while (++pos.y < end)
    {
      pos.x = (prog->win_size.x / prog->all_client * (prog->nb_client - 1)) - 1;
      while (++pos.x < (prog->win_size.x / prog->all_client * prog->nb_client))
	{
	  pixel_color.full = calcul_pixel(prog, raycast, pos);
	  tekpixel(prog->pix, &pos, &pixel_color);
	}
    }
  prog->rendu_success -= (thread_id + 1);
  pthread_exit(NULL);
}

int			raytrace_thread_create(t_prog *prog, int i,
					       pthread_t thread_id[])
{
  prog->rendu_success += i + 1;
  if (pthread_create(&thread_id[i], NULL,
		     ((prog->rendu_verticale) ? (raytrace_verticale)
		      : (raytrace_horizontale)), (void *)prog))
    return (my_printf(2, "Error: can not create thread\n") - 1);
  return (0);
}

static int		raytrace_end(t_prog *prog, pthread_t thread_id[],
				     time_t time_beg, t_bunny_position *pos)
{
  int			i;
  time_t		time_end;

  i = -1;
  while (++i < prog->thread_nb)
    pthread_join(thread_id[i], NULL);
  time_end = time(NULL);
  if (prog->verbose)
    my_printf(1, "\nRendu en %d heures %d minutes %d secondes\n",
	      (time_end - time_beg) / 3600, ((time_end - time_beg) % 3600) / 60,
	      ((time_end - time_beg) % 3600) % 60);
    bunny_blit(&prog->win->buffer, &prog->pix->clipable, pos);
  bunny_display(prog->win);
  if (prog->verbose)
    my_putstr("Raytracing multi-threading successfull\n");
  return (0);
}

int			raytrace_threading(t_prog *prog, int nb_client,
					  int all_client)
{
  pthread_t		thread_id[prog->thread_nb];
  time_t		time_beg;
  t_bunny_position      pos;
  int			i;

  pos.x = 0;
  pos.y = 0;
  prog->nb_client = nb_client;
  prog->all_client = all_client;
  if (prog->verbose)
    my_putstr("\nRaytracing multi-threading started\n");
  i = -1;
  if (prog->verbose)
    my_putstr("\nStarting create thread\n");
  prog->rendu_success = 0;
  time_beg = time(NULL);
  while (++i < prog->thread_nb)
    {
      if (raytrace_thread_create(prog, i, thread_id))
	return (-1);
      usleep(10000);
    }
  if (prog->verbose)
    my_putstr("Thread create successfull\n");
  while (prog->display_rendu && (prog->rendu_success > 0))
    {
      bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
      bunny_display(prog->win);
    }
  return (raytrace_end(prog, thread_id, time_beg, &pos));
}
