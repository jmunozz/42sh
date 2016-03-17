# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboos <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 15:35:19 by tboos             #+#    #+#              #
#    Updated: 2016/03/17 15:22:49 by tboos            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY: fclean re
.SUFFIXES:
NAME = minishell
DNAME = d_minishell
FLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -Weverything
SRC = main.c ft_minishell.c free.c ft_errors.c
SRCS = $(foreach S, $(SRC), srcs/$(S))
OBJ = $(SRCS:.c=.o)
HEAD = -I libft -I includes

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(HEAD) $^ -L libft -l ft -o $@

%.o: %.c
	gcc $(FLAGS) $(HEAD)  -c $^ -o $@

lib:
	make -C libft

$(DNAME): lib
	gcc $(DFLAGS) $(OBJ) $(HEAD) libft/libft.a -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(DNAME)
	make -C libft fclean

re: fclean all
	make -C libft re

re: fclean lib $(DNAME)
