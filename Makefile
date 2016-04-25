##
## Makefile for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
## 
## Made by victor sousa
## Login   <sousa_v@epitech.net>
## 
## Started on  Tue Feb  9 01:56:43 2016 victor sousa
## Last update Mon Apr 25 00:23:03 2016 Kerdelhue Ethan
##

NAME		=	raytracer2

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"

SRCDIR		=	src

INCDIR		=	inc
LIBDIR		=	lib

RM		=	rm -f

CC		=	gcc
CFLAGS		=	-W -Wall -Wextra -DMACRO	\
			-ansi -pedantic				\
			-I/home/${USER}/.froot/include		\
			-I$(INCDIR)

LDFLAGS		=	-L/home/${USER}/.froot/lib		\
			-llapin					\
			-L/usr/local/lib			\
			-lsfml-audio				\
			-lsfml-graphics				\
			-lsfml-window				\
			-lsfml-system				\
			-lstdc++ -ldl				\
			-lm

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
SRC		+=	src/hit/hit.c				\
			src/hit/sphere.c			\
			src/hit/triangle.c

##  RAYTRACE  ##
SRC		+=	src/raytrace/raytrace.c			\
			src/raytrace/shad_n_light.c		\
			src/raytrace/reflect.c			\
			src/raytrace/obj_calculs.c

##  XML  ##
SRC		+=	src/xml/get_field.c

##  EDITEUR  ##
SRC		+=	src/editeur/editor.c

##  UTILS  ##
SRC		+=	src/utils/my_tablen.c			\
			src/utils/my_str_to_wordtab.c		\
			src/utils/str_to_wordtab.c		\
			src/utils/my_strstr.c			\
			src/utils/my_strlen.c			\
			src/utils/my_strcat.c			\
			src/utils/my_getnbr.c			\
			src/utils/my_realloc.c			\
			src/utils/key_handle.c			\
			src/utils/get_next_line.c		\
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

all:			title $(NAME)

title		:
			@$(ECHO) $(GREEN)Raytracer$(TEAL)2$(DEFAULT)

$(NAME)		:	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) &&	\
			$(ECHO) $(GREEN) "[OK]" $(TEAL) $(NAME) $(DEFAULT) ||	\
			$(ECHO) $(RED) "[XX]" $(TEAL) $(NAME) $(DEFAULT)

.c.o		:
			@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ &&		\
			$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) ||	\
			$(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

clean		:
			@$(RM) $(OBJ)

fclean		:	clean
			@$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
