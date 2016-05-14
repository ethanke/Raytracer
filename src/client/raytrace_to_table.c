/*
** raytrace_to_table.c for raytracer in /Users/leandr_g/Documents/Shared folder/Raytracer/src/client/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sat May 14 03:17:37 2016 Gaëtan Léandre
** Last update Sat May 14 06:15:56 2016 Gaëtan Léandre
*/

#include		"main.h"

void			*raytrace_horizontale_client(void *p)
{
  static int		thread_id = -1;
  t_pass		*pass;
  t_prog		*prog;
  t_raycast		raycast;
  t_bunny_position      pos;
  int			end;

  pass = p;
  prog = pass->prog;
  raycast.touch_circle = 0;
  pos.y = ((prog->win_size.y / prog->thread_nb) * ++thread_id) - 1;
  end = ((prog->win_size.y / prog->thread_nb) * (thread_id + 1));
  if (prog->verbose)
    my_printf(1, "Thread number %d : %d to %d\n", thread_id, pos.y, end);
  while (++pos.y < end)
    {
      pos.x = prog->start - 1;
      while (++pos.x < prog->stop)
	pass->grille[pos.x - prog->start + pos.y * (prog->stop - prog->start)] = calcul_pixel(prog, raycast, pos);
    }
  prog->rendu_success -= (thread_id + 1);
  pthread_exit(NULL);
}

int			raytrace_thread_create_client(t_pass *pass, int i,
						      pthread_t thread_id[])
{
  pass->prog->rendu_success += i + 1;
  if (pthread_create(&thread_id[i], NULL, raytrace_horizontale_client, (void *)pass))
    return (my_printf(2, "Error: can not create thread\n") - 1);
  return (0);
}

static unsigned int	*raytrace_end_client(t_pass *pass, pthread_t thread_id[],
					     time_t time_beg)
{
  int			i;
  time_t		time_end;
  t_prog		*prog;

  prog = pass->prog;
  i = -1;
  while (++i < prog->thread_nb)
    pthread_join(thread_id[i], NULL);
  time_end = time(NULL);
  if (prog->verbose)
    my_printf(1, "\nRendu en %d heures %d minutes %d secondes\n", (time_end - time_beg) / 3600, ((time_end - time_beg) % 3600) / 60, ((time_end - time_beg) % 3600) % 60);
  if (prog->verbose)
    my_putstr("Raytracing multi-threading successfull\n");
  return (pass->grille);
}

unsigned int		*raytrace_threading_client(t_prog *prog, int start,
						   int stop)
{
  pthread_t		thread_id[prog->thread_nb];
  time_t		time_beg;
  int			i;
  t_pass		pass;

  prog->start = start;
  prog->stop = stop;
  if ((pass.grille = malloc(sizeof(unsigned int) * (stop - start) * prog->win_size.y)) == NULL)
    return (NULL);
  if (prog->verbose)
    my_putstr("\nRaytracing multi-threading started\n");
  i = -1;
  if (prog->verbose)
    my_putstr("\nStarting create thread\n");
  prog->rendu_success = 0;
  pass.prog = prog;
  time_beg = time(NULL);
  while (++i < prog->thread_nb)
    {
      if (raytrace_thread_create_client(&pass, i, thread_id))
	return (NULL);
      usleep(10000);
    }
  if (prog->verbose)
    my_putstr("Thread create successfull\n");
/*  while (prog->display_rendu && (prog->rendu_success > 0))
    {
      bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
      bunny_display(prog->win);
    }*/
  return (raytrace_end_client(&pass, thread_id, time_beg));
}
