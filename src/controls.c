/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 00:18:03 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/21 23:34:42 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	controls(int key, t_cub *cub, int state)
{
	if (key == 13)
		cub->player.keys[MOVE_F] = state;
	else if (key == 126)
		cub->player.keys[MOVE_F_2] = state;
	else if (key == 1)
		cub->player.keys[MOVE_B] = state;
	else if (key == 125)
		cub->player.keys[MOVE_B_2] = state;
	else if (key == 123)
		cub->player.keys[ROT_L] = state;
	else if (key == 124)
		cub->player.keys[ROT_R] = state;
	else if (key == 0)
		cub->player.keys[STRAFE_L] = state;
	else if (key == 2)
		cub->player.keys[STRAFE_R] = state;
	else if (key == 53)
		exit_clean(cub);
	return (0);
}

int			key_down(int key, t_cub *cub)
{
	return (controls(key, cub, 1));
}

int			key_up(int key, t_cub *cub)
{
	return (controls(key, cub, 0));
}
