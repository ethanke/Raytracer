##
## Makefile for test in /home/leandr_g/Shared/testServer
##
## Made by
## Login   <leandr_g@epitech.net>
##
## Started on  Wed May  4 23:49:13 2016
## Last update Mon May 16 10:26:15 2016 Philippe Lefevre
##

NAME		=	client

CFLAGS		=	-W -Wall -Werror -pedantic		\
			-I./include -lm				\
			-g

PRTFDIR		=	src/my_printf

SRC		=	src/client.c				\
			src/client_raytrace.c			\
			src/command.c				\
			src/communicate.c			\
			src/raytrace_to_table.c			\
			src/send_file.c				\
			src/my_strcat.c				\
			src/image/disp_image.c			\
			src/image/hitbox_creator.c		\
			src/image/load_image.c

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

SRC		+=	src/get_next_line.c			\
			src/utils.c				\
			src/str_to_wordtab.c			\
			src/send_file.c				\
			src/xml/get_field.c			\
			src/xml/get_field_bis.c			\
			src/my_getnbr.c

OBJ		=	$(SRC:.c=.o)


all		:	$(NAME)

$(NAME)		:	$(OBJ)
			gcc -o $(NAME) $(OBJ)

clean		:
			rm -rf $(OBJ)

fclean		:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
