/*
** load_screen.c for Raytrace in /home/lefevr_h/Workspace/Github/Raytracer/src/loading/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Thu May 12 12:11:50 2016 Philippe Lefevre
** Last update Thu May 12 12:37:46 2016 Philippe Lefevre
*/

#include		"main.h"

int			waiting_screen(t_prog *prog)
{
  t_bunny_position      pos;
  t_texture		*loading;

  pos.x = 0;
  pos.y = 0;
  if ((loading = load_image("sprites/image/loading.jpg")) == NULL)
    return (-1);
  put_image(loading, prog->pix, &pos);
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, &pos);
  bunny_display(prog->win);
  /* delete t_texture*/
  return (0);
}
