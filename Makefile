# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboos <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 17:44:49 by tboos             #+#    #+#              #
#    Updated: 2016/09/13 16:25:25 by rbaran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: fclean re
.SUFFIXES:
NAME = 21sh
FLAGS = -Wall -Wextra -Werror
FLAGSPOSIX = -ansi -pedantic -D_POSIX_SOURCE=1
SRCS = $(foreach S, $(SRC), srcs/$(S))
OBJ = $(SRCS:.c=.o)
TERMCAPS = -lm -lncurses
HEAD = -I libft/includes -I includes
OS = $(shell uname -s)
SRC = \
builtins/builtin.c \
builtins/environ.c \
core/cmp.c \
core/errors.c \
core/free.c \
core/hash.c \
core/main.c \
core/minishell.c \
core/signal.c \
history/history.c \
history/history_search_up.c \
history/history_search_down.c \
history/history_backup.c \
history/scanchr.c \
history/searchengine.c \
history/scanchr.c \
history/sprompt.c \
run_command/files.c \
run_command/fork.c \
scan_input/arrowlr.c \
scan_input/arrowud.c \
scan_input/autocomp.c \
scan_input/chrparse.c \
scan_input/deletion.c \
scan_input/prompt.c \
scan_input/quotecheck.c \
scan_input/streamscan.c \
scan_input/termcaps.c \
scan_input/winsize.c \

ifeq ($(OS), Linux)
	FLAGS += -D LINUX
endif

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(HEAD) $^ -L libft -l ft -o $@ $(TERMCAPS)

%.o: %.c libft/libft.a
	gcc $(FLAGS) $(HEAD) -c $< -o $@

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
