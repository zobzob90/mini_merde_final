# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 11:30:29 by ertrigna          #+#    #+#              #
#    Updated: 2024/11/15 11:56:11 by ertrigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a

CC =	cc

FLAGS =	-Wall -Wextra -Werror

RM =	rm -f

FILES = print_hexa.c print_int.c print_ptr.c print_str.c \
		print_unsigned_int.c ft_printf.c

OBJS = $(FILES:.c=.o)

.c.o :
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS)
		ar rc $(NAME) $(OBJS)

all :	$(NAME)

clean :
	$(RM) $(OBJS)

fclean :	clean
			$(RM) $(NAME)

re : fclean all