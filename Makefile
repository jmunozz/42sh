# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboos <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 15:35:19 by tboos             #+#    #+#              #
#    Updated: 2016/03/08 19:12:51 by tboos            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
DNAME = d_ft_ls
FLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -Weverything
SRC = main.c ft_minishell.c
PATH = srcs/
OBJ = $(PATH)$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $^

lib:
	cd libft ; make

$(NAME): lib $(OBJ)
	gcc $(FLAGS) $(OBJ) -I libft -I includes libft/libft.a -o $(NAME)

$(DNAME): lib
	gcc $(DFLAGS) $(PATH)$(SRC) -I libft -I includes libft.a -o $(DNAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(DNAME)

re: fclean $(NAME)
dre: fclean $(DNAME)
.PHONY: fclean re
