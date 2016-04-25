/*
** main.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Tue Feb  9 01:50:10 2016 victor sousa
** Last update Mon Apr 25 04:03:22 2016 victor sousa
*/

#include		"main.h"

int			verif_arg(int ac, char **av, char **env)
{
  if (env == NULL)
    return (-1);
  if (ac != 2)
    {
      my_putstr("usage: ./raytracer1 [path/to/scene.xml]\n");
      my_putstr("       ./raytracer1 --edit\n");
      return (-1);
    }
  if (my_strstr("--edit", av[1]))
    {
      editor();
      return (-1);
    }
  return (0);
}

int			verif_load(t_prog *prog, char **av)
{
 if (load_scene(prog, av[1]) == -1)
    {
      my_putstr("scene   loading  failed... leaving\n");
      return (-1);
    }
  else
    my_putstr("scene   loading  successfull\n");
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
			      false, "Raytracer 1")) == NULL)
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

  if (verif_arg(ac, av, env) != 0 ||
      verif_load(&prog, av) != 0 ||
      create_pix(&prog) != 0 ||
      create_win(&prog) != 0)
    return (-1);
  bunny_set_key_response(key);
  raytrace(&prog);
  my_putstr("\nStarting the loop display\n");
  bunny_set_loop_main_function(mainloop);
  bunny_loop(prog.win, 30, &prog);
  free_stuff(&prog);
  return (0);
}
