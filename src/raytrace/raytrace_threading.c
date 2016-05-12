/*
** raytrace_threading.c for Raytracer in /home/lefevr_h/Workspace/Github/Raytracer/src/raytrace/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Sun May  8 02:20:22 2016 Philippe Lefevre
** Last update Thu May 12 11:26:50 2016 Philippe Lefevre
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
  prog->thread_success -= (prog->thread_id + 1);
  while (prog->thread_success > 0);
  while (++pos.x < end)
    {
      pos.y = -1;
      while (++pos.y < prog->win_size.y)
	{
	  pixel_color.full = calcul_pixel(prog, raycast, pos);
	  tekpixel(prog->pix, &pos, &pixel_color);
	}
    }
    prog->rendu_success -= (prog->thread_id + 1);
  pthread_exit(NULL);
}

int			raytrace_threading(t_prog *prog)
{
  pthread_t		thread_id[prog->thread_nb];
  t_texture		*loading;
  time_t		time_thread;
  time_t		time_beg;
  time_t		time_end;
  t_bunny_position      pos;
  int			i;

  pos.x = 0;
  pos.y = 0;
  if ((loading = load_image("sprites/image/loading.jpg")) == NULL)
    return (-1);
  put_image(loading, prog->pix, &pos);
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
  bunny_display(prog->win);
  prog->thread_success = 0;
  i = -1;
  while (++i < prog->thread_nb)
    prog->thread_success += i +1;
  my_putstr("\nRaytracing multi-threading started\n");
  i = -1;
  time_beg = time(NULL);
  my_putstr("\nStarting create thread\n");
  prog->rendu_success = 0;
  while (++i < prog->thread_nb)
    {
      prog->thread_id = i;
      prog->rendu_success += i + 1;
      pthread_create(&thread_id[i], NULL, raytrace_zone, (void *)prog);
      time_thread = time(NULL);
      while (time_thread == time(NULL));
    }
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
