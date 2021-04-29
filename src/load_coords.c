/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_coords.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:40:31 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/12 20:57:58 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** plane.x = -0.66 / 0.66 for NORTH/SOUTH;  0    		for EAST/WEST
** plane.y =  0			  for NORTH/SOUTH; -0.66 / 0.66 for EAST/WEST
**
** dir.x, dir.y : -1,  0 == WEST;  1, 0 == EAST
** dir.x, dir.y :  0, -1 == NORTH; 0, 1 == SOUTH
*/

static void	set_player_coords(t_player *player, int y, int x, char *cell)
{
	player->x = x + 0.5;
	player->y = y + 0.5;
	if (*cell == 'N' || *cell == 'S')
	{
		player->plane.x = (*cell == 'N') ? -0.66 : 0.66;
		player->plane.y = 0;
		player->dir.x = 0;
		player->dir.y = (*cell == 'N') ? -1 : 1;
	}
	else
	{
		player->plane.x = 0;
		player->plane.y = (*cell == 'W') ? 0.66 : -0.66;
		player->dir.x = (*cell == 'W') ? -1 : 1;
		player->dir.y = 0;
	}
	*cell = '0';
}

static void	load_sprite(t_coords *sprite, int y, int x)
{
	sprite->x = x;
	sprite->y = y;
}

static void	load_all_coords(t_cub *cub, int size)
{
	int i;
	int j;
	int k;

	if (!(cub->sprite = malloc(sizeof(t_coords) * size)))
		exit_err(cub, 0, E_SPRITE_MALLOC);
	i = 0;
	k = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (size > 0 && cub->map[i][j] == '2')
				load_sprite(&cub->sprite[k++], i, j);
			else if (ft_strchr(cub->map[i][j], "NESW"))
				set_player_coords(&cub->player, i, j, &cub->map[i][j]);
			j++;
		}
		i++;
	}
}

static int	count_all_coords(char **map, int *sprite_count, int *num_player)
{
	int i;
	int j;

	*sprite_count = 0;
	*num_player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				*sprite_count += 1;
			else if (ft_strchr(map[i][j], "NESW"))
				*num_player += 1;
			else if (!ft_strchr(map[i][j], "01 "))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void		load_coords(t_cub *cub)
{
	int	num_player;

	if (count_all_coords(cub->map, &cub->sprite_count, &num_player) < 0)
		exit_err(cub, E_MAP_CHAR, 0);
	if (num_player != 1)
		exit_err(cub, E_MAP_PLAYER, 0);
	cub->sprite = 0;
	load_all_coords(cub, cub->sprite_count);
}
