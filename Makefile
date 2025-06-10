NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinc -Ilibft
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS = src/main.c \
		src/signal/signal.c \
		src/env/init_env.c \
		src/env/get_env_value.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_init.c \
		src/lexer/quotes.c \
		src/lexer/print_debug.c \
		src/expand/expand.c \
		src/expand/join.c \
		src/parsing/parsing_utils.c \
		src/parsing/pars_init.c \
		src/parsing/parsing.c \
		src/exec/exec_builtin.c \
		src/exec/exec_external.c \
		src/exec/exec_child.c \
		src/exec/exec_heredoc.c \
		src/exec/exec_main.c \
		src/exec/exec_path.c \
		src/exec/exec_redir.c \
		src/exec/exec_utils.c \
		src/exec/exec_wait.c \
		src/builtin/cd.c \
		src/builtin/echo.c \
		src/builtin/exit.c \
		src/builtin/launch.c \
		src/builtin/pwd.c \
		src/builtin/unset.c \
		src/builtin/export_utils.c \
		src/builtin/export.c \
		src/easter/michel.c \
		src/easter/michel_prompt.c \
		src/utils/free.c \
		src/utils/builtin_utils.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
		$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(INC) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
		rm -f $(OBJS)
		$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
		rm -f $(NAME)
		$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

