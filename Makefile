##
## Makefile for Semestre 1 in /home/guillaume1chanut/Semestre 1/Rush/rush1
##
## Made by chanut
## Login   <guillaume1chanut@epitech.net>
##
## Started on  Fri Mar 03 23:35:07 2017 chanut
## Last update Fri Mar 03 23:35:07 2017 chanut
##

CC	= gcc

CFLAGS	= -Iinclude -Wextra -Wall

RM	= rm -f

SRCS	= ./main.c	 		\
	  ./tools.c			\
	  ./get_next_ligne.c

OBJS	= $(SRCS:.c=.o)

NAME	= my_archive

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
