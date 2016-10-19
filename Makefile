# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaran <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/27 09:55:48 by rbaran            #+#    #+#              #
#*   Updated: 2016/06/01 16:08:03 by rbaran           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = minishell
GCC = gcc -Wall -Werror -Wextra
SRCS =	srcs/builtins/ft_cd.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_exit.c \
		srcs/builtins/ft_setenv.c \
		srcs/builtins/ft_unsetenv.c \
		srcs/ft_access.c \
		srcs/ft_error.c \
		srcs/ft_exec.c \
		srcs/ft_fillconf.c \
		srcs/ft_findbuiltin.c \
		srcs/ft_findcmd.c \
		srcs/ft_free.c \
		srcs/ft_hash.c \
		srcs/ft_manageenv.c \
		srcs/ft_managelst.c \
		srcs/ft_minishell.c \
		srcs/ft_printprompt.c \
		srcs/ft_util.c \
		srcs/main.c \
		srcs/scaninput/ft_erase.c \
		srcs/scaninput/ft_move.c \
		srcs/scaninput/ft_putchar_int.c \
		srcs/scaninput/ft_saverestore.c \
		srcs/scaninput/ft_scanchr.c \
		srcs/scaninput/ft_scaninput.c \
		srcs/scaninput/ft_history.c
OBJ = $(SRCS:.c=.o)
LIBFT = -Llibft/ -lft
LIBCURSE = -lcurses
INCLUDES = -I includes/ -I libft/includes/

all: LIB $(NAME)

LIB:
	@make -C libft/

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME) $(LIBFT) $(LIBCURSE)

%.o: %.c
	$(GCC) $^ -c -o $@ $(INCLUDES)

clean:
	/bin/rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all LIB re
