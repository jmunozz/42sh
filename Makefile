# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboos <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 15:35:19 by tboos             #+#    #+#              #
#    Updated: 2016/03/23 17:44:20 by tboos            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY: fclean re
.SUFFIXES:
NAME = minishell
DNAME = d_minishell
FLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -Weverything
SRC = main.c minishell.c free.c errors.c prompt.c cmp.c hash.c streamscan.c
SRCS = $(foreach S, $(SRC), srcs/$(S))
OBJ = $(SRCS:.c=.o)
HEAD = -I libft/includes -I includes

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $^ $(HEAD) -L libft -l ft -o $@

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
