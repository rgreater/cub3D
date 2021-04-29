/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 22:58:58 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/15 14:23:12 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	safe_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = 0;
	}
}

static void	safe_mlx_destroy_image(void *mlx, t_data *img)
{
	if (img)
	{
		mlx_destroy_image(mlx, img);
		img = 0;
	}
}

static void	free_all(t_cub *cub)
{
	int i;

	if (cub->map)
	{
		i = 0;
		while (i < cub->map_size.y)
			safe_free(cub->map[i++]);
		safe_free(cub->map);
	}
	safe_free(cub->sprite);
	safe_free(cub->z_buf);
	safe_free(cub->texture.n.path);
	safe_free(cub->texture.s.path);
	safe_free(cub->texture.w.path);
	safe_free(cub->texture.e.path);
	safe_free(cub->texture.sprite.path);
	safe_mlx_destroy_image(cub->mlx, cub->texture.e.data.img);
	safe_mlx_destroy_image(cub->mlx, cub->texture.w.data.img);
	safe_mlx_destroy_image(cub->mlx, cub->texture.n.data.img);
	safe_mlx_destroy_image(cub->mlx, cub->texture.s.data.img);
	safe_mlx_destroy_image(cub->mlx, cub->texture.sprite.data.img);
	safe_mlx_destroy_image(cub->mlx, cub->frame.img);
	if (cub->window)
		mlx_destroy_window(cub->mlx, cub->window);
	safe_free(cub->mlx);
}

void		exit_err(t_cub *cub, const char *err_msg, const char *err_arg)
{
	puterr(ERROR);
	if (err_msg)
	{
		puterr(err_msg);
		if (err_arg)
		{
			puterr(": ");
			puterr(err_arg);
		}
	}
	else
		perror(err_arg);
	free_all(cub);
	exit(-1);
}

int			exit_clean(t_cub *cub)
{
	free_all(cub);
	exit(0);
	return (0);
}
