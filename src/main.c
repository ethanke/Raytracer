/*
** main.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 01:50:10 2016 victor sousa
** Last update Mon May 16 09:56:39 2016 Philippe Lefevre
*/

#include		"main.h"

int			disp_help(char *bin)
{
  my_printf(1, "Usage: %s scene[.xml|.obj]\n", bin);
  my_printf(1, "	--thread=nb_thread	Number of thread using. ");
  my_printf(1, "Default=1\n");
  my_printf(1, "	--cluster\n");
  my_printf(1, "	--display_rendu		Rendering in real time\n");
  my_printf(1, "	--rendu_verticale	Split rendering zone in verticale ");
  my_printf(1, "mode for the thread. Default is horizontale\n");
  my_printf(1, "	--verbose		Display all details message ");
  my_printf(1, "[time|status]\n");
  my_printf(1, "	--credit		Display credit for author\n");
  my_printf(1, "	OR\n");
  my_printf(1, "Usage: %s --edit\n", bin);
  return (-1);
}

int			disp_credit(char **av)
{
  int			i;

  i = 0;
  while (av[++i])
    if (!(my_strcmp("--credit", av[i])))
      return (my_printf(1, "Credit Raytracer Epitech\n")
              + my_printf(1, "	Leandre Gaetan\n")
              + my_printf(1, "	Sousa Victor\n")
              + my_printf(1, "	Lefevre Philippe\n")
              + my_printf(1, "	Kerdelhue Ethan\n") - 1);
  return (0);
}

int			create_pix(t_prog *prog)
{
  if ((prog->pix = bunny_new_pixelarray(prog->win_size.x, prog->win_size.y))
      == NULL)
    {
      my_putstr("buffer   creation failed... leaving\n");
      return (-1);
    }
  else
    my_putstr("buffer  creation successfull\n");
  return (0);
}

int			create_win(t_prog *prog)
{
  if ((prog->win = bunny_start(prog->win_size.x, prog->win_size.y,
			       false, "Raytracer 2")) == NULL)
    {
      my_putstr("windows creation failed... leaving\n");
      return (-1);
    }
  else
    my_putstr("windows creation successfull\n");
  return (0);
}

int			main(int ac, char **av, char **env)
{
  t_prog		prog;

  set_max_heap_size(RT_MAX_RAM);
  if (verif_env(env))
    return (-1);
  if ((ac < 2) || verif_arg(ac, av, &prog))
    return (-1);
  if (prog.cluster)
    {
      if (client(&prog) == -1)
	return (-1);
    }
  else if (create_pix(&prog) || create_win(&prog) || waiting_screen(&prog))
    return (-1);
  else
    raytrace_threading(&prog, 0, ((prog.rendu_verticale) ?
				  (prog.win_size.y) : (prog.win_size.x)));
  bunny_set_key_response(key);
  bunny_set_loop_main_function(mainloop);
  bunny_loop(prog.win, 30, &prog);
  free_stuff(&prog);
  return (0);
}
