/*
** object.h for  in /home/sousa_v/rendu/lapin/rtv2/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Fri May  6 00:19:16 2016 Victor Sousa
** Last update Fri May  6 00:36:39 2016 Victor Sousa
*/

class Vec3f
{
  float	x;
  float	y;
  float	z;
}

class Vec3
{
  int	x;
  int	y;
  int	z;
}

class Vec2f
{
  float	x;
  float	y;
}

class Vec2
{
  int	x;
  int	y;
}

class Color
{
  float	r;
  float	g;
  float	b;
}

class Image
{
  String	file_path;
  Vec2		size;
  Color		pixel[size.x][size.y];
}

class Camera
{
  Vec3f		start;
  Vec3f		look_at;
  Vec3f		direction;
  Vec2f		rotation;
  Vec2f		fov;
  int		alliasing;
}

class Light
{
  Vec3f		center;
  float		intensity;
}

class Mat
{
  int		id;
  Color		color;
  float		reflect;
  float		bump;
  Image		texture;
}

class Object
{
  Vec3f	center;
  Vec3f normale;
  Mat	material;
}

class Sphere : Object
{
  float radius;
}

class Plan : Object
{
  Vec3f 	dir;
  Mat	material2;
}

class Circle : Object
{
  Vec3f 	dir;
  float radius;
}

class Cylinder : Object
{
  Vec3f		dir;
  float 	radius;
  float 	height;
  Circle	cap[2];
}

class Triangle : Object
{
  Vec3f		point[3];
}

class Cone : Object
{
  Vec3f 		dir;
  float		radius;
  float		height;
  Circle	cap;
}

class Pill :Objec
{
  Cylinder	body;
  Sphere	cap[2];
}
