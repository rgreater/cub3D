# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgreater <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 14:35:16 by rgreater          #+#    #+#              #
#    Updated: 2021/03/22 18:20:47 by rgreater         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
HDR_DIR =	./src/headers/
LIB_DIR	=	./lib/
LFT_DIR =	$(LIB_DIR)libft/
MLX_DIR	=	$(LIB_DIR)mlx_opengl/
CFLAGS	=	-Wall -Wextra -Werror -O2 -I$(HDR_DIR) -I$(LFT_DIR) -I$(MLX_DIR)
HEADER	=	$(LFT_DIR)libft.h $(MLX_DIR)mlx.h $(HDR_DIR)cub3d.h $(HDR_DIR)errmsg.h
NAME	=	cub3D
SRCS	=	$(addprefix src/,\
			load_cub.c\
			bmp.c\
			controls.c\
			movement.c\
			color.c\
			read_cub.c\
			parse_settings.c\
			load_map.c\
			load_coords.c\
			load_textures.c\
			map_validation.c\
			main.c\
			draw_frame.c\
			draw_bg.c\
			texture_draw.c\
			sprite_draw.c\
			sprite_sort.c\
			window.c\
			exit.c)
OBJS	=	$(SRCS:.c=.o)
MLX		=	$(MLX_DIR)libmlx.a
LIBFT	=	$(LFT_DIR)libft.a
ALL_LIB =	-L$(LFT_DIR) -lft -L$(MLX_DIR) -lmlx

all:		lft lmlx $(NAME)	

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(ALL_LIB) -framework OpenGL -framework AppKit -o $@

%.o:		%.c $(HEADER) $(MLX) $(LIBFT) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

lft:
			@$(MAKE) -j -C $(LFT_DIR)

lmlx:
			@$(MAKE) -j -C $(MLX_DIR)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

libclean:	clean
			@$(MAKE) clean -j -C $(LFT_DIR)
			@$(MAKE) clean -j -C $(MLX_DIR)

libfclean:	fclean
			@$(MAKE) fclean -j -C $(LFT_DIR)
			@$(MAKE) fclean -j -C $(MLX_DIR)

libre:		libfclean all

.PHONY:		all clean fclean re libclean libfclean re bonus
