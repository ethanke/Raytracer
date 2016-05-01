/*
** image.h for image in /Users/leandr_g/Documents/Shared folder/TekAdventure/inc/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Fri Apr 15 03:26:21 2016 Gaëtan Léandre
** Last update Sun May  1 14:42:15 2016 Gaëtan Léandre
*/

 #ifndef   _IMAGE_H_
 # define  _IMAGE_H_

 # define  PLACE_IMG_ALPHA  60

 typedef struct          s_texture
 {
   int                   width;
   int                   height;
   t_color               **color;
 }                       t_texture;

 typedef struct          s_hitbox
 {
   int                   x;
   int                   y;
   int                   width;
   int                   height;
 }                       t_hitbox;

 t_texture        	*load_image(const char *file);
 t_texture  		*pix_array_to_texture(t_bunny_pixelarray *pix);
 void   		put_image(t_texture *bmp,
				  t_bunny_pixelarray *pix,
				  t_bunny_position *pos);
 void   		place_image(t_hitbox pos,
				    t_hitbox fetch,
				    t_texture *tex,
				    t_bunny_pixelarray *pix);
 void   		redim_image(t_hitbox *pos,
				    t_texture *tex,
				    t_bunny_pixelarray *pix);
t_texture		*create_text_uni(int width, int height,
					 unsigned int col);
 #endif   /*_IMAGE_H_*/
