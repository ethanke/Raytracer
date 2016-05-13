##
## Makefile for raytracer1 in /home/sousa_v/rendu/lapin/gfx_raytracer1
##
## Made by victor sousa
## Login   <sousa_v@epitech.net>
##
## Started on  Tue Feb  9 01:56:43 2016 victor sousa
## Last update Fri May 13 23:24:42 2016 Philippe Lefevre
##

NAME		=	raytracer2

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"

SRCDIR		=	src

PRTFDIR		=	src/editeur/my_printf
SPRTFDIR	=	src/editeur/my_sprintf
EDITDIR		=	src/editeur
LOADIR		=	src/loading
HITDIR		=	src/hit

INCDIR		=	inc
LIBDIR		=	lib

RM		=	rm -f

CC		=	gcc
CFLAGS		=	-W -Wall -Wextra -DMACRO -g3 -ggdb \
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
			-lm -lpthread

##  MAIN  ##
SRC		=	src/main.c				\
			src/loop.c				\
			src/end.c

## LOADING ##
SRC		+=	$(LOADIR)/parsing_scene.c		\
			$(LOADIR)/load_mat.c			\
			$(LOADIR)/load_mtl.c			\
			$(LOADIR)/load_mat_param.c		\
			$(LOADIR)/load_light.c			\
			$(LOADIR)/load_obj.c			\
			$(LOADIR)/load_sphere_param.c		\
			$(LOADIR)/load_triangle_param.c		\
			$(LOADIR)/load_cone_params.c		\
			$(LOADIR)/load_cyl_params.c		\
			$(LOADIR)/load_cube_param.c		\
			$(LOADIR)/load_pill_params.c		\
			$(LOADIR)/load_plan_params.c		\
			$(LOADIR)/load_obj_file.c		\
			$(LOADIR)/load_vertex.c			\
			$(LOADIR)/load_forme.c			\
			$(LOADIR)/load_screen.c

##  HIT  ##
SRC		+=	$(HITDIR)/hit.c				\
			$(HITDIR)/sphere.c			\
			$(HITDIR)/triangle.c			\
			$(HITDIR)/cone.c				\
			$(HITDIR)/cube.c				\
			$(HITDIR)/cylinder.c			\
			$(HITDIR)/plan.c

##  RAYTRACE  ##
SRC		+=	src/raytrace/raytrace.c			\
			src/raytrace/raytrace_threading.c	\
			src/raytrace/shad_n_light.c		\
			src/raytrace/reflect.c			\
			src/raytrace/obj_calculs.c

##  XML  ##
SRC		+=	src/xml/get_field.c			\
			src/xml/get_field_bis.c

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

## SPRINTF ##
SRC             +=      $(SPRTFDIR)/my_disp_unprintable.c    	\
                        $(SPRTFDIR)/my_sprintf.c               	\
                        $(SPRTFDIR)/my_sprintf2.c              	\
                        $(SPRTFDIR)/my_sprintf3.c              	\
                        $(SPRTFDIR)/my_put_nbr.c              	\
                        $(SPRTFDIR)/my_put_u_nbr_base.c        	\
                        $(SPRTFDIR)/my_put_unbr.c               \
                        $(SPRTFDIR)/my_putnbr_base.c            \
                        $(SPRTFDIR)/my_putnbr_base_add.c        \
			$(SPRTFDIR)/my_put_fnbr.c		\
			$(SPRTFDIR)/my_strcat.c

SRC		+=	$(EDITDIR)/aff_light.c			\
			$(EDITDIR)/aff_mat.c			\
			$(EDITDIR)/add_obj.c			\
			$(EDITDIR)/add_mat.c			\
			$(EDITDIR)/edit_obj.c			\
			$(EDITDIR)/edit_light.c			\
			$(EDITDIR)/push_func.c			\
			$(EDITDIR)/edit_cam.c			\
			$(EDITDIR)/edit_cam_bis.c		\
			$(EDITDIR)/aff_obj.c			\
			$(EDITDIR)/aff_win.c			\
			$(EDITDIR)/add_light.c			\
			$(EDITDIR)/cmd.c			\
			$(EDITDIR)/count.c			\
			$(EDITDIR)/utils.c			\
			$(EDITDIR)/edit_mat.c			\
			$(EDITDIR)/write_xml.c

##  IMAGE  ##
SRC		+=	src/image/load_image.c			\
			src/image/disp_image.c			\
			src/image/hitbox_creator.c

##  UTILS  ##
SRC		+=	src/utils/tekpixel.c			\
			src/utils/my_tablen.c			\
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

##  CLIENT  ##
SRC		+=	src/client/client.c			\
			src/client/communicate.c		\
			src/client/command.c			\
			src/client/send_file.c			\
			src/client/client_raytrace.c

##  OUTPUT  ##
SRC		+=	src/output/my_putchar.c			\
			src/output/my_putstr.c			\
			src/output/my_put_nbr.c			\
			src/output/my_strlen.c

##  TCORE  ##


OBJ		=	$(SRC:.c=.o)

all:			title $(NAME)

title		:
			@$(ECHO) $(GREEN)Raytracer$(TEAL)2$(DEFAULT)

$(NAME)		:	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) &&	\
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
