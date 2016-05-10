##
## Makefile for test in /home/leandr_g/Shared/testServer
##
## Made by
## Login   <leandr_g@epitech.net>
##
## Started on  Wed May  4 23:49:13 2016
## Last update Mon May  9 11:09:26 2016
##

NAME		=	server

CFLAGS		=	-I./include -W -Wall -Werror

SRC		=	server_src/main.c			\
			server_src/comunicate.c			\
			server_src/command.c			\
			server_src/connection.c			\
			server_src/reciv_img.c

SRC_A		=	commun/get_next_line.c			\
			commun/utils.c				\
			commun/str_to_wordtab.c			\
			commun/send_file.c

OBJ		=	$(SRC:.c=.o)

OBJ_A		=	$(SRC_A:.c=.o)

all		:	$(NAME)

$(NAME)		:	$(OBJ) $(OBJ_A)
			gcc -o $(NAME) $(OBJ) $(OBJ_A)

clean		:
			rm -rf $(OBJ) $(OBJ_A)

fclean		:	clean
			rm -rf $(NAME)

re		:	fclean all
