/*
** main.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 01:50:10 2016 victor sousa
** Last update Tue May 10 23:28:19 2016 Philippe Lefevre
*/

#include		"main.h"

int			verif_load(t_prog *prog, char *args)
{
  int			ret;

  ret = -1;
  if (args[my_strlen(args) - 1] == 'l' &&
      args[my_strlen(args) - 2] == 'm' &&
      args[my_strlen(args) - 3] == 'x' &&
      args[my_strlen(args) - 4] == '.')
    ret = load_scene(prog, args);
  else if (args[my_strlen(args) - 1] == 'j' &&
	   args[my_strlen(args) - 2] == 'b' &&
	   args[my_strlen(args) - 3] == 'o' &&
	   args[my_strlen(args) - 4] == '.')
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
  my_printf(1, "Usage: %s [path/to/scene.xml] [--thread={nb thread}]\n", bin);
  my_printf(1, "  OR   %s [path/to/scene.obj] [--thread={nb thread}]\n", bin);
  my_printf(1, "  OR   %s --edit\n", bin);
  return (-1);
}

int			verif_arg(int ac, char **av, char **env, t_prog *prog)
{
  int			i;
  int			ret;

  i = 0;
  if (env == NULL)
    return (-1);
  if (ac < 2 || ac > 3)
    return (disp_help(av[0]));
  prog->thread_nb = 0;
  while (av[++i])
    if ((ret = verif_load(prog, av[i])))
      {
	if (ret == -1)
	  return (ret);
      }
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

int			main(int ac, char *av[], char *env[])
{
  t_prog		prog;

  set_max_heap_size(521);
  if (verif_arg(ac, av, env, &prog) != 0
      || create_pix(&prog) != 0
      || create_win(&prog) != 0)
    return (-1);
  bunny_set_key_response(key);
  if (!prog.thread_nb)
    raytrace(&prog);
  else
    raytrace_threading(&prog);
  bunny_set_loop_main_function(mainloop);
  bunny_loop(prog.win, 30, &prog);
  free_stuff(&prog);
  return (0);
}
