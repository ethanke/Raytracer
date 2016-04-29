## 
## Makefile for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
##
## Made by victor sousa
## Login   <sousa_v@epitech.net>
##
## Started on  Tue Feb  9 01:56:43 2016 victor sousa
## Last update Wed Apr 27 12:46:22 2016 Kerdelhue Ethan
##

NAME		=	raytracer2

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"

SRCDIR		=	src

PRTFDIR		=	src/editeur/my_printf
EDITDIR		=	src/editeur

INCDIR		=	inc
LIBDIR		=	lib

RM		=	rm -f

CC		=	gcc
CFLAGS		=	-W -Wall -Wextra -DMACRO -g3 -ggdb \
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
			src/loading/load_triangle_param.c	\
			src/loading/load_cone_params.c		\
			src/loading/load_plan_params.c		\
			src/loading/load_obj_file.c		\
			src/loading/load_vertex.c		\
			src/loading/load_forme.c

##  HIT  ##
SRC		+=	src/hit/hit.c				\
			src/hit/sphere.c			\
			src/hit/triangle.c			\
			src/hit/cone.c				\
			src/hit/plan.c

##  RAYTRACE  ##
SRC		+=	src/raytrace/raytrace.c			\
			src/raytrace/shad_n_light.c		\
			src/raytrace/reflect.c			\
			src/raytrace/obj_calculs.c

##  XML  ##
SRC		+=	src/xml/get_field.c

##  EDITEUR  ##
SRC		+=	src/editeur/editor.c

## PRINTF ##

SRC             +=      $(PRTFDIR)/my_disp_unprintable.c        \
                        $(PRTFDIR)/my_printf.c                  \
                        $(PRTFDIR)/my_printf2.c                 \
                        $(PRTFDIR)/my_printf3.c                 \
                        $(PRTFDIR)/my_put_nbr.c                 \
                        $(PRTFDIR)/my_put_u_nbr_base.c          \
                        $(PRTFDIR)/my_put_unbr.c                \
                        $(PRTFDIR)/my_putchar.c                 \
                        $(PRTFDIR)/my_putnbr_base.c             \
                        $(PRTFDIR)/my_putnbr_base_add.c         \
                        $(PRTFDIR)/my_putstr.c			\
			$(PRTFDIR)/my_put_fnbr.c		

SRC		+=	$(EDITDIR)/aff_light.c			\
			$(EDITDIR)/aff_mat.c			\
			$(EDITDIR)/add_obj.c			\
			$(EDITDIR)/add_mat.c			\
			$(EDITDIR)/edit_obj.c			\
			$(EDITDIR)/aff_obj.c			\
			$(EDITDIR)/aff_win.c			\
			$(EDITDIR)/add_light.c			\
			$(EDITDIR)/cmd.c			\
			$(EDITDIR)/count.c			\
			$(EDITDIR)/utils.c			\
			$(EDITDIR)/write_xml.c

##  UTILS  ##
SRC		+=	src/utils/my_tablen.c			\
			src/utils/my_str_to_wordtab.c		\
			src/utils/str_to_wordtab.c		\
			src/utils/my_strstr.c			\
			src/utils/my_atof.c			\
			src/utils/my_strlen.c			\
			src/utils/my_strcat.c			\
			src/utils/my_getnbr.c			\
			src/utils/my_get_float.c		\
			src/utils/my_realloc.c			\
			src/utils/key_handle.c			\
			src/utils/get_next_line.c		\
			src/utils/vect_operator.c		\
			src/utils/vect_operator2.c		\
			src/utils/wtf.c				\
			src/utils/epur_str.c

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
