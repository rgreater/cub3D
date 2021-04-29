/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 22:20:06 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/21 23:33:24 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_string(char *map_name, char *str_w, char *str_h, char *str)
{
	int		len_w;
	int		len_h;

	len_w = ft_strlen(str_w);
	len_h = ft_strlen(str_h);
	ft_memmove(str, "cub3D - ", 8);
	ft_memmove((str + 8), map_name, ft_strlen(map_name));
	ft_memmove((str + 8 + ft_strlen(map_name)), " (", 2);
	ft_memmove((str + 10 + ft_strlen(map_name)), str_w, len_w);
	free(str_w);
	ft_memmove((str + 10 + ft_strlen(map_name) + len_w), " x ", 3);
	ft_memmove((str + 13 + ft_strlen(map_name) + len_w), str_h, len_h);
	free(str_h);
	ft_memmove((str + 13 + ft_strlen(map_name) + len_w + len_h), ")", 2);
	return (str);
}

/*
** malloc size:
** 15 == strlen("cub3D -  ( x )") + 1
*/

static char	*get_window_title(t_cub *cub, char *map_name)
{
	char	*str_w;
	char	*str_h;
	char	*str;

	str_w = ft_itoa(cub->screen.width);
	if (!str_w)
		exit_err(cub, 0, E_WIN_TITLE);
	str_h = ft_itoa(cub->screen.height);
	if (!str_h)
	{
		free(str_w);
		exit_err(cub, 0, E_WIN_TITLE);
	}
	str = malloc(sizeof(char) * (ft_strlen(str_w) + ft_strlen(str_h) + 15 +
														ft_strlen(map_name)));
	if (!str)
	{
		free(str_w);
		free(str_h);
		exit_err(cub, 0, E_WIN_TITLE);
	}
	return (get_string(map_name, str_w, str_h, str));
}

void		win_init(t_cub *cub, char *filename)
{
	char	*title;
	int		i;

	title = get_window_title(cub, filename);
	if (!title)
		exit_err(cub, 0, E_WIN_TITLE);
	cub->window = mlx_new_window(cub->mlx, cub->screen.width,
									cub->screen.height, title);
	free(title);
	if (cub->window == NULL)
		exit_err(cub, E_MLX_WIN, 0);
	draw_frame(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->frame.img, 0, 0);
	i = 0;
	while (i < 8)
		cub->player.keys[i++] = 0;
}
