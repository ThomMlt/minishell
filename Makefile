# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 15:23:37 by lidbaha           #+#    #+#              #
#    Updated: 2025/06/16 15:37:58 by tmillot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = core/minishell.c \
		  utils/env/cpy_env.c \
		  utils/cleaning/clean.c \
		  utils/built_in/ft_cd.c \
		  utils/exec/executing.c \
		  utils/exec/processus.c \
		  utils/exec/free_shell.c \
		  utils/exec/trim_quote.c \
		  utils/built_in/ft_env.c \
		  utils/built_in/ft_pwd.c \
		  utils/parsing/parsing.c \
		  utils/built_in/ft_exit.c \
		  utils/built_in/ft_echo.c \
		  utils/built_in/ft_unset.c \
		  utils/checking/checking.c \
          utils/exec/find_command.c \
		  utils/built_in/ft_export.c \
		  utils/checking/checking_2.c \
		  utils/list_init/list_init.c \
		  utils/exec/exit_free_exec.c \
		  utils/exec/handle_env_exec.c \
		  utils/exec/processus_utils.c \
		  utils/exec/executing_utils.c \
		  utils/exec/signals_handler.c \
		  utils/exec/handling_dollars.c \
		  utils/exec/open_redirection.c \
		  utils/split/ft_strdup_split.c \
		  utils/split/ft_strndup_split.c \
		  utils/exec/speciale_built_in.c \
		  utils/exec/error_message_exec.c \
		  utils/exec/expand_trim_quotes.c \
		  utils/built_in/utils_built_in.c \
		  utils/exec/redirect_management.c \
		  utils/parsing/here_doc/here_doc.c \
		  utils/parsing/fill_cmd/fill_cmd.c \
		  utils/strcmp/ft_strcmp_minishell.c \
		  utils/exec/handling_dollars_utils.c \
		  utils/parsing/fill_cmd/fill_cmd_2.c \
		  utils/parsing/fill_cmd/fill_cmd_3.c \
		  utils/parsing/divide/ft_divide_str.c \
		  utils/parsing/divide/ft_divide_char.c \
		  utils/parsing/divide/ft_divide_str_2.c \
		  utils/parsing/parse_redir/parse_redir.c \
		  utils/parsing/parse_redir/parse_redir_2.c \
		  utils/parsing/divide/ft_divide_char_all.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

OBJS = $(SOURCES:.c=.o)

GNL_DIR = ./includes/get_next_line
LIBFT_DIR = ./includes/libft

GNL_LIB = $(GNL_DIR)/libgnl.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(GNL_DIR) -I$(LIBFT_DIR) -I/usr/include
LDFLAGS = -L$(GNL_DIR) -lgnl -L$(LIBFT_DIR) -g -lft -L/usr/lib -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(GNL_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(GNL_LIB):
	make -C $(GNL_DIR)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(GNL_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(GNL_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all