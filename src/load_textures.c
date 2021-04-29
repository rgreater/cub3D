/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 00:15:07 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 14:02:02 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_cub *cub, t_texture *t)
{
	int fd;

	fd = open(t->path, O_RDONLY);
	if (fd < 0)
		exit_err(cub, 0, t->path);
	close(fd);
	if (ft_strlen(t->path) >= 4 && ft_strncmp_lcase(
			t->path + ft_strlen(t->path) - 4, ".xpm", 4) == 0)
		t->data.img = mlx_xpm_file_to_image(cub->mlx, t->path, &t->width,
											&t->height);
	else if (ft_strlen(t->path) >= 4 && ft_strncmp_lcase(
			t->path + ft_strlen(t->path) - 4, ".png", 4) == 0)
		exit_err(cub, E_PNG, 0);
	else
		exit_err(cub, E_TEX_FILEXT, 0);
	if (t->data.img == NULL)
		exit_err(cub, t->path, E_MLX_IMG);
	free(t->path);
	t->path = 0;
	t->data.addr = mlx_get_data_addr(t->data.img, &t->data.bits_per_pixel,
									&t->data.line_length, &t->data.endian);
	if (t->data.addr == NULL)
		exit_err(cub, E_MLX_ADRR, 0);
	t->data.bits_per_pixel /= 8;
}

void		load_textures(t_cub *cub)
{
	load_texture(cub, &cub->texture.n);
	load_texture(cub, &cub->texture.s);
	load_texture(cub, &cub->texture.e);
	load_texture(cub, &cub->texture.w);
	load_texture(cub, &cub->texture.sprite);
}
