/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 03:31:19 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/21 23:33:08 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef REG_MODE
#  define REG_MODE 0
# endif
# ifndef SAVE_BMP
#  define SAVE_BMP 1
# endif
# ifndef DEG
#  define DEG 0.01745329252
# endif
# ifndef VELOCITY
#  define VELOCITY 0.1
# endif
# ifndef NORTH
#  define NORTH	3
# endif
# ifndef SOUTH
#  define SOUTH	2
# endif
# ifndef EAST
#  define EAST 1
# endif
# ifndef WEST
#  define WEST 0
# endif
# ifndef MOVE_F
#  define MOVE_F 0
# endif
# ifndef MOVE_B
#  define MOVE_B 1
# endif
# ifndef ROT_L
#  define ROT_L 2
# endif
# ifndef ROT_R
#  define ROT_R 3
# endif
# ifndef STRAFE_L
#  define STRAFE_L 4
# endif
# ifndef STRAFE_R
#  define STRAFE_R 5
# endif
# ifndef MOVE_F_2
#  define MOVE_F_2 6
# endif
# ifndef MOVE_B_2
#  define MOVE_B_2 7
# endif
# ifndef BMP_HDR_START
#  define BMP_HDR_START "\0\0\0\0\x36\0\0\0\x28\0\0\0"
# endif
# ifndef BMP_HDR_E
#  define BMP_HDR_E "\1\0\30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
# endif

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "errmsg.h"

typedef struct		s_screen
{
	int				width;
	int				height;
	double			aspect_r;
}					t_screen;

typedef struct		s_color
{
	int				ceil;
	int				floor;
}					t_color;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_texture
{
	char			*path;
	t_data			data;
	int				width;
	int				height;
}					t_texture;

typedef struct		s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef struct		s_coords_f
{
	double			x;
	double			y;
}					t_coords_f;

typedef struct		s_raycast
{
	double			ray_pos;
	double			wall_dist;
	double			wall_hit;
	t_coords_f		sidedist;
	t_coords_f		raydir;
	t_coords_f		ddist;
	t_coords		inc;
	t_coords		map;
	int				side;
	int				line_h;
}					t_raycast;

typedef struct		s_sprite
{
	double			inv_det;
	double			depth;
	double			x;
	double			y;
	t_coords		draw;
	t_coords		draw_end;
	int				screen_x;
	int				height;
	int				width;
}					t_sprite;

typedef struct		s_draw_tex
{
	int				draw_start;
	int				draw_end;
	int				y;
	double			step;
	t_texture		*t;
}					t_draw_tex;

typedef struct		s_player
{
	double			x;
	double			y;
	t_coords_f		dir;
	t_coords_f		plane;
	int				keys[8];
}					t_player;

typedef struct		s_textures
{
	t_texture		n;
	t_texture		s;
	t_texture		w;
	t_texture		e;
	t_texture		sprite;
}					t_textures;

typedef struct		s_cub
{
	void			*mlx;
	void			*window;
	t_data			frame;
	t_screen		screen;
	t_textures		texture;
	t_color			color;
	char			**map;
	t_coords		map_size;
	t_player		player;
	t_coords		*sprite;
	int				sprite_count;
	double			*z_buf;
}					t_cub;

int					load_cub(t_cub *cub, char *filename, int save);
void				read_cubfile(t_cub *cub, char *filename);
int					parse_settings(char *line, t_cub *cub, int *flag);
void				load_map(t_cub *cub, t_list **list);
void				map_validation(t_cub *cub);
void				load_coords(t_cub *cub);
void				load_textures(t_cub *cub);
void				win_init(t_cub *cub, char *filename);
void				draw_frame(t_cub *cub);
void				draw_bg(t_screen *s, t_data *frame, t_color *color);
void				draw_sprites(t_cub *cub, t_player *p);
void				draw_texture(t_cub *cub, t_raycast *r, int screen_x);
void				quick_sort(t_coords *arr, t_player *p, int start, int end);
int					get_pixel_color(t_data *data, int x, int y);
int					key_down(int key, t_cub *cub);
int					key_up(int key, t_cub *cub);
int					move_player(t_cub *cub);
int					save_bmp(t_cub *cub, char *map_name);
int					exit_clean(t_cub *cub);
void				exit_err(t_cub *cub, const char *err_msg,
										const char *err_arg);

#endif
