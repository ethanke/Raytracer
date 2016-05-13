/*
** main.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 01:50:10 2016 victor sousa
** Last update Fri May 13 23:23:46 2016 Philippe Lefevre
*/

#include		"main.h"

int			verif_load(t_prog *prog, char *args)
{
  int			ret;
  int			size;

  size = my_strlen(args);
  ret = -1;
  if (args[size - 1] == 'l' &&
      args[size - 2] == 'm' &&
      args[size - 3] == 'x' &&
      args[size - 4] == '.')
    ret = load_scene(prog, args);
  else if (args[size - 1] == 'j' &&
	   args[size - 2] == 'b' &&
	   args[size - 3] == 'o' &&
	   args[size - 4] == '.')
    ret = load_obj_file(prog, args);
  else
    return (0);
  if (ret == -1)
    {
      my_putstr("scene   loading  failed... leaving\n");
      return (-1);
    }
  else
    my_putstr("scene   loading  successfull\n");
  return (1);
}

int			disp_help(char *bin)
{
  my_printf(1, "Usage: %s scene[.xml|.obj]\n", bin);
  my_printf(1, "	--thread=nb_thread	Number of thread using. Default=1\n", bin);
  my_printf(1, "	--cluster\n", bin);
  my_printf(1, "	--display_rendu		Rendering in real time\n", bin);
  my_printf(1, "	--rendu_verticale	Split rendering zone in verticale mode for the thread. Default is horizontale\n", bin);
  my_printf(1, "	--edit\n", bin);
  my_printf(1, "	--verbose		Display all details message [time|status]\n", bin);
  my_printf(1, "	--credit		Display credit for author\n", bin);
  return (-1);
}

int			verif_arg(int ac, char **av, char **env, t_prog *prog)
{
  int			i;
  int			ret;

  if (env == NULL)
    return (-1);
  if (ac < 2)
    return (disp_help(av[0]));
  i = 0;
  while (av[++i])
    if (!(my_strcmp("--credit", av[i])))
	return (my_printf(1, "Credit Raytracer Epitech\n")
		+ my_printf(1, "	Leandre Gaetan\n")
		+ my_printf(1, "	Sousa Victor\n")
		+ my_printf(1, "	Lefevre Philippe\n")
		+ my_printf(1, "	Kerdelhue Ethan\n") - 1);
  prog->thread_nb = 1;
  prog->cluster = 0;
  prog->display_rendu = 0;
  prog->rendu_verticale = 0;
  prog->verbose = 0;
  i = 0;
  while (av[++i])
    {
      if ((ret = verif_load(prog, av[i])))
	{
	  if (ret == -1)
	    return (ret);
	}
      else if (!(my_strcmp("--cluster", av[i])))
	{
	  prog->cluster = 1;
      	  return (client(prog));
	}
      else if (!(my_strcmp("--display_rendu", av[i])))
	prog->display_rendu = 1;
      else if (!(my_strcmp("--rendu_verticale", av[i])))
	prog->rendu_verticale = 1;
      else if (!(my_strcmp("--verbose", av[i])))
	prog->verbose = 1;
      else if (!(my_strncmp("--thread=", av[i], 9)))
	{
	  prog->thread_nb = my_getnbr(av[i] + 9);
	  if (prog->thread_nb < 1)
	    return (my_printf(2, "Error: number of thread must be positive\n") - 1);
	}
      else if (!(my_strcmp("--edit", av[i])))
	{
	  if (prog->thread_nb)
	    return (disp_help(av[0]));
	  return (editor() - 1);
	}
      else
	return (disp_help(av[0]));
    }
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
  if (verif_arg(ac, av, env, &prog) || create_pix(&prog)
      || create_win(&prog) || waiting_screen(&prog))
    return (-1);
  bunny_set_key_response(key);
  if (prog.cluster)
    {
      if (client(&prog) == -1)
	return (-1);
    }
  else
    raytrace_threading(&prog, 1, 1);
  bunny_set_loop_main_function(mainloop);
  bunny_loop(prog.win, 30, &prog);
  free_stuff(&prog);
  return (0);
}
