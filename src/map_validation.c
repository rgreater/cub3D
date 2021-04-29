/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 23:19:55 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 03:26:15 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_vertical(char **map, int i, size_t j, int *visited)
{
	int k;

	if (i < 1 || j < 1)
		return (-1);
	if (visited[j] <= i && (ft_strlen(map[i - 1]) <= j || map[i - 1][j] != '1'))
		return (-1);
	if (i > visited[j] && map[i - 1][j] == '1')
	{
		if (visited[j] > 0 && map[visited[j]][j] != '1')
			return (-1);
		k = 1;
		while (map[i + k] && j < ft_strlen(map[i + k]) &&
						(map[i + k][j] == '0' || map[i + k][j] == '2'))
			k++;
		if (!map[i + k] || ft_strlen(map[i + k]) < j ||
										map[i + k][j] != '1')
			return (-1);
		visited[j] = i + k;
	}
	return (0);
}

static int	check_horizontal(char **map, int i, int *visited)
{
	size_t j;

	j = 0;
	while (j < ft_strlen(map[i]))
	{
		while (map[i][j] == ' ')
			j++;
		while (map[i][j] == '1')
			j++;
		if (map[i][j] == '0' || map[i][j] == '2')
		{
			if (j < 1 || map[i][j - 1] != '1')
				return (-1);
			while (map[i][j] == '0' || map[i][j] == '2')
			{
				if (check_vertical(map, i, j, visited) < 0)
					return (-1);
				j++;
			}
			if (map[i][j] != '1')
				return (-1);
		}
		j++;
	}
	return (0);
}

static int	map_iterate(char **map, int line_count, int *visited)
{
	int i;

	i = 0;
	while (i < line_count)
	{
		if (check_horizontal(map, i, visited) < 0)
			return (-1);
		i++;
	}
	return (0);
}

void		map_validation(t_cub *cub)
{
	int i;
	int *visited;
	int ret;

	load_coords(cub);
	if (!(visited = malloc(sizeof(int) * cub->map_size.x)))
		exit_err(cub, 0, 0);
	i = 0;
	while (i < cub->map_size.x)
		visited[i++] = 0;
	ret = map_iterate(cub->map, cub->map_size.y, visited);
	free(visited);
	if (ret < 0)
		exit_err(cub, E_MAP, 0);
}
