# **************************************************************************** #
#                                LIBFT MAKEFILE                                #
# **************************************************************************** #

# Nom de la bibliothèque
NAME = libft.a

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Fichiers sources
SRCS = ft_atoi.c ft_atol.c ft_free_tab.c ft_putchar_fd.c ft_putendl_fd.c \
       ft_putstr_fd.c ft_split.c ft_strcmp.c ft_strdup.c ft_strjoin.c \
       ft_strlen.c ft_strncmp.c ft_strncpy.c ft_strndup.c ft_substr.c \
	   ft_isalnum.c ft_bzero.c ft_calloc.c ft_strcpy.c ft_strcat.c \
	   ft_itoa.c ft_strjoin_free.c ft_isdigit.c ft_isalpha.c ft_isspace.c \
	   ft_strlcpy.c ft_strspn.c ft_strjoin_ctrl_free.c

# Dossiers contenant des fichiers supplémentaires
PRINTF_DIR = ft_printf
GNL_DIR = get_next_line

# Fichiers de ft_printf
PRINTF_SRCS = $(addprefix $(PRINTF_DIR)/, ft_printf.c print_hexa.c print_int.c \
               print_ptr.c print_str.c print_unsigned_int.c)

# Fichiers de get_next_line
GNL_SRCS = $(addprefix $(GNL_DIR)/, get_next_line.c get_next_line_utils.c)

# Tous les fichiers sources
ALL_SRCS = $(SRCS) $(PRINTF_SRCS) $(GNL_SRCS)

# Objets
OBJS = $(ALL_SRCS:.c=.o)

# En-têtes
HEADERS = -I. -I$(PRINTF_DIR) -I$(GNL_DIR)

# Commandes
RM = rm -f
AR = ar rcs

# **************************************************************************** #
#                                  RÈGLES                                      #
# **************************************************************************** #

# Compilation de la bibliothèque
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "✅ Compilation de $(NAME) terminée."

# Compilation des fichiers objets
%.o: %.c libft.h $(PRINTF_DIR)/ft_printf.h $(GNL_DIR)/get_next_line.h
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@$(RM) $(OBJS)
	@echo "🧹 Suppression des fichiers objets terminée."

# Nettoyage complet (objets + bibliothèque)
fclean: clean
	@$(RM) $(NAME)
	@echo "🗑️ Suppression de $(NAME) terminée."

# Recompilation complète
re: fclean all

# Éviter que Make considère ces noms comme des fichiers
.PHONY: all clean fclean re
