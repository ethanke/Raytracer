##
## Makefile for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
## 
## Made by victor sousa
## Login   <sousa_v@epitech.net>
## 
## Started on  Tue Feb  9 01:56:43 2016 victor sousa
## Last update Sun Mar 13 22:38:13 2016 victor sousa
##

NAME		=	raytracer1

CFLAGS		=	-L/home/${USER}/.froot/lib/ -llapin 	\
			-I/home/${USER}/.froot/include/		\
			-L/usr/local/lib 			\
			-lsfml-audio 				\
			-lsfml-graphics 			\
			-lsfml-window 				\
			-lsfml-system 				\
			-lstdc++ -ldl -lm			\
			-Iincludes

CFLAGS		+=	-W -Wall -ansi -pedantic

##  MAIN  ##
SRC		=	src/main.c				\
			src/loop.c				\
			src/end.c

## LOADING ##
SRC		+=	src/loading/parsing_scene.c		\
			src/loading/load_mat.c			\
			src/loading/load_mat_param.c		\
			src/loading/load_light.c		\
			src/loading/load_obj.c			\
			src/loading/load_sphere_param.c		\
			src/loading/load_triangle_param.c

##  HIT  ##
SRC		+=	src/hit/sphere.c			\
			src/hit/hit.c

##  RAYTRACE  ##
SRC		+=	src/raytrace/raytrace.c			\
			src/raytrace/shad_n_light.c		\
			src/raytrace/reflect.c			\
			src/raytrace/obj_calculs.c

##  XML  ##
SRC		+=	src/xml/get_field.c

##  UTILS  ##
SRC		+=	src/utils/my_tablen.c			\
			src/utils/my_str_to_wordtab.c		\
			src/utils/my_strstr.c			\
			src/utils/my_strcat.c			\
			src/utils/my_getnbr.c			\
			src/utils/my_realloc.c			\
			src/utils/key_handle.c			\
			src/utils/vect_operator.c		\
			src/utils/vect_operator2.c		\
			src/utils/wtf.c

##  OUTPUT  ##
SRC		+=	src/output/my_putchar.c			\
			src/output/my_putstr.c			\
			src/output/my_put_nbr.c			\
			src/output/my_strlen.c

##  TCORE  ##
SRC		+=	tcore/tekpixel.c


OBJ		=	$(SRC:.c=.o)


all:			$(NAME)

$(NAME):		$(OBJ)
			gcc $(OBJ) $(CFLAGS) -o $(NAME)

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

re:			fclean all
