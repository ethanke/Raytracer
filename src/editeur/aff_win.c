/*
** aff_win.c for  in /Users/ethankerdelhue/Documents/Shared/Raytracer/src/editeur/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Tue Apr 26 10:06:01 2016 Ethan Kerdelhue
** Last update Tue Apr 26 10:06:33 2016 Ethan Kerdelhue
*/

#include		"main.h"

int			aff_win_prop(int fd, t_prog *prog)
{
  my_printf(fd, "\t<view>\n");
  my_printf(fd, "\t\t<x_size>");
  my_printf(fd, "%d", prog->win_size.x);
  my_printf(fd, "</x_size>\n");
  my_printf(fd, "\t\t<y_size>");
  my_printf(fd, "%d", prog->win_size.y);
  my_printf(fd, "</y_size>\n");
  my_printf(fd, "\t\t<cam_pos>\n\t\t\t<x>%d</x>\n", prog->cam_pos.x);
  my_printf(fd, "\t\t\t<y>%d</y>\n\t\t\t<z>%d</z>\n\t\t</cam_pos>\n",
	    prog->cam_pos.y, prog->cam_pos.z);
  my_printf(fd, "\t</view>\n");
  return (0);
}
