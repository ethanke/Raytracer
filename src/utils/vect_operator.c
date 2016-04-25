/*
** vect_operator.c for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Tue Mar  8 22:59:09 2016 victor sousa
** Last update Fri Mar 11 00:10:25 2016 victor sousa
*/

#include		"main.h"

float                   mult_vector(const t_coord *v1, const t_coord *v2)
{
  return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_coord                 minus_vector(const t_coord *v1, const t_coord *v2)
{
  t_coord               out;

  out.x = v1->x - v2->x;
  out.y = v1->y - v2->y;
  out.z = v1->z - v2->z;
  return (out);
}

t_coord                 add_vector(const t_coord *v1, const t_coord *v2)
{
  t_coord               out;

  out.x = v1->x + v2->x;
  out.y = v1->y + v2->y;
  out.z = v1->z + v2->z;
  return (out);
}

t_coord			float_time_vector(float c, const t_coord *v)
{
  t_coord		out;

  out.x = v->x * c;
  out.y = v->y * c;
  out.z = v->z * c;
  return (out);
}
