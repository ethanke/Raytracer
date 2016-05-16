/*
** main.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 01:50:10 2016 victor sousa
** Last update Mon May 16 09:54:05 2016 Philippe Lefevre
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

int			verif_env(char **env)
{
  int			i;

  if (env == NULL)
    return (-1);
  i = -1;
  while (env[++i])
    {
      if (!(my_strncmp(env[i], "DISPLAY=", 8)))
	return (0);
    }
  return (-1);
}

int			init_rendu(char *arg, t_prog *prog)
{
  if (!(my_strcmp("--display_rendu", arg)))
    {
      prog->display_rendu = 1;
      return (1);
    }
  else if (!(my_strcmp("--rendu_verticale", arg)))
    {
      prog->rendu_verticale = 1;
      return (1);
    }
  return (0);
}

int			init_opt(char *arg, t_prog *prog)
{
  if (!(my_strcmp("--verbose", arg)))
    {
      prog->verbose = 1;
      return (1);
    }
  else if (!(my_strncmp("--thread=", arg, 9)))
    {
      prog->thread_nb = my_getnbr(arg + 9);
      return (1);
    }
  return (0);
}

int			verif_arg(int ac, char **av, t_prog *prog)
{
  int			i;
  int			ret;

  if (disp_credit(av) || editor(ac, av))
    return (-1);
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
      	  return (0);
	}
      else if (init_rendu(av[i], prog) || init_opt(av[i], prog))
	continue;
      else
	return (disp_help(av[0]));
    }
  if (prog->thread_nb < 1)
    return (my_printf(2, "Number of thread must be positive\n") - 1);
  return (0);
}
