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

NAME = ft_ls
DNAME = d_ft_ls
FLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -Weverything
SRC = main.c manage_list.c manage_list_next.c ft_ls.c manage_arg.c manage_file.c

all: $(NAME)

lib:
	cd libft ; make ; cp libft.a ../.

$(NAME): lib
	gcc $(FLAGS) $(SRC) -I libft libft.a -o $(NAME)

$(DNAME): lib
	gcc $(DFLAGS) $(SRC) -I libft libft.a -o $(DNAME)

clean:
	rm -f libft.a

fclean: clean
	rm -f $(NAME)
	rm -f $(DNAME)

re: fclean $(NAME)
dre: fclean $(DNAME)
.PHONY: fclean re
