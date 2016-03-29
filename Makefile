# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboos <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 15:35:19 by tboos             #+#    #+#              #
#    Updated: 2016/03/29 16:15:29 by tboos            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY: fclean re
.SUFFIXES:
NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC = main.c minishell.c free.c errors.c prompt.c cmp.c hash.c streamscan.c \
	fork.c builtin.c files.c history.c environ.c
SRCS = $(foreach S, $(SRC), srcs/$(S))
OBJ = $(SRCS:.c=.o)
HEAD = -I libft/includes -I includes

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $^ $(HEAD) -L libft -l ft -o $@

%.o: %.c libft/libft.a
	gcc $(FLAGS) $(HEAD)  -c $< -o $@

lib:
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

re: fclean lib $(DNAME)
