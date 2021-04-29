/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 00:19:35 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 15:27:25 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**		When the program runs in "--save" mode, resolution is capped to
**	make sure that the resulting .BMP image is less than ~805 MB,
**	hence the weird number: 0x30000000L.
**		Also, max length/width is set to 16384.
*/

static void	check_resolution(t_cub *cub, int save)
{
	t_screen	*s;
	int			max_w;
	int			max_h;

	s = &cub->screen;
	if (!save)
	{
		mlx_get_screen_size(cub->mlx, &max_w, &max_h);
		if (s->width > max_w)
			s->width = max_w;
		if (s->height > max_h)
			s->height = max_h;
	}
	else if ((long)s->width * (long)s->height > 0x30000000L)
	{
		if (s->width > 0x4000)
			s->width = 0x4000;
		if (s->height > 0x4000)
			s->height = 0x4000;
	}
	s->aspect_r = (double)s->width / (double)s->height / 1.313;
}

static void	mlx_frame_init(t_cub *cub, int save)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		exit_err(cub, E_MLX_INIT, 0);
	check_resolution(cub, save);
	cub->frame.img = mlx_new_image(cub->mlx, cub->screen.width,
											cub->screen.height);
	if (cub->frame.img == NULL)
		exit_err(cub, E_MLX_IMG, 0);
	cub->frame.addr = mlx_get_data_addr(
			cub->frame.img, &cub->frame.bits_per_pixel,
			&cub->frame.line_length, &cub->frame.endian);
	if (cub->frame.addr == NULL)
		exit_err(cub, E_MLX_ADRR, 0);
	cub->frame.bits_per_pixel /= 8;
	if (cub->sprite_count > 0)
	{
		cub->z_buf = malloc(sizeof(double) * cub->screen.width);
		if (!cub->z_buf)
			exit_err(cub, 0, "z_buffer");
	}
}

static void	init_variables(t_cub *cub)
{
	cub->map = 0;
	cub->map_size.x = 0;
	cub->map_size.y = 0;
	cub->sprite_count = 0;
	cub->z_buf = 0;
	cub->texture.e.path = 0;
	cub->texture.n.path = 0;
	cub->texture.w.path = 0;
	cub->texture.s.path = 0;
	cub->texture.sprite.path = 0;
	cub->texture.e.data.img = 0;
	cub->texture.n.data.img = 0;
	cub->texture.w.data.img = 0;
	cub->texture.s.data.img = 0;
	cub->texture.sprite.data.img = 0;
	cub->frame.img = 0;
	cub->mlx = 0;
	cub->window = 0;
}

int			load_cub(t_cub *cub, char *filename, int save)
{
	init_variables(cub);
	read_cubfile(cub, filename);
	mlx_frame_init(cub, save);
	load_textures(cub);
	if (save)
		return (save_bmp(cub, filename));
	win_init(cub, filename);
	return (0);
}
