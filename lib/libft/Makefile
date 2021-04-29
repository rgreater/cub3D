# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgreater <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 14:35:16 by rgreater          #+#    #+#              #
#    Updated: 2021/03/22 14:41:20 by rgreater         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O2 -I.
HEADER	=	libft.h get_next_line.h
NAME	=	libft.a
SRCS	=	src/atoi_itoa.c \
			src/ft_tolower.c \
			src/ft_memmove.c \
			src/list.c \
			src/string.c \
			src/get_next_line.c \
			src/get_next_line_utils.c \
			src/puterr.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) Makefile
			ar rcs $(NAME) $(OBJS)

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
