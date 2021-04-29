/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:34:54 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 15:01:35 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move(t_player *p, char **map, int dir)
{
	int		mv;
	double	vel;

	mv = 0;
	vel = 0.1;
	if (dir < 0)
		vel -= 0.025;
	if (map[(int)p->y][(int)(p->x + p->dir.x * dir * 0.75)] != '1')
	{
		mv = 1;
		p->x += p->dir.x * dir * vel;
	}
	if (map[(int)(p->y + p->dir.y * dir * 0.75)][(int)p->x] != '1')
	{
		mv = 1;
		p->y += p->dir.y * dir * vel;
	}
	return (mv);
}

static int	strafe(t_player *p, char **map, int dir)
{
	int		mv;
	double	vel;

	mv = 0;
	vel = 0.1;
	if (map[(int)p->y][(int)(p->x + p->plane.x * dir * 0.5)] != '1')
	{
		mv = 1;
		p->x += p->plane.x * dir * vel;
	}
	if (map[(int)(p->y + p->plane.y * dir * 0.5)][(int)p->x] != '1')
	{
		mv = 1;
		p->y += p->plane.y * dir * vel;
	}
	return (mv);
}

static int	rotate(t_player *p, int dir)
{
	double dir_x;
	double plane_x;
	double vel;

	vel = dir * 2;
	dir_x = p->dir.x;
	p->dir.x = p->dir.x * cos(vel * DEG) - p->dir.y * sin(vel * DEG);
	p->dir.y = dir_x * sin(vel * DEG) + p->dir.y * cos(vel * DEG);
	plane_x = p->plane.x;
	p->plane.x = p->plane.x * cos(vel * DEG) - p->plane.y * sin(vel * DEG);
	p->plane.y = plane_x * sin(vel * DEG) + p->plane.y * cos(vel * DEG);
	return (1);
}

static void	check_borders(t_player *p, char **map)
{
	if (map[(int)p->y + 1][(int)p->x] == '1' && ((p->y - (int)p->y) > 0.75))
		p->y = (int)p->y + 0.75;
	if (map[(int)p->y][(int)p->x + 1] == '1' && ((p->x - (int)p->x) > 0.75))
		p->x = (int)p->x + 0.75;
	if (map[(int)p->y - 1][(int)p->x] == '1' && ((p->y - (int)p->y) < 0.25))
		p->y = (int)p->y + 0.25;
	if (map[(int)p->y][(int)p->x - 1] == '1' && ((p->x - (int)p->x) < 0.25))
		p->x = (int)p->x + 0.25;
}

int			move_player(t_cub *cub)
{
	int	*keys;
	int	mv;

	keys = cub->player.keys;
	mv = 0;
	if (keys[ROT_L] && !keys[ROT_R])
		mv += rotate(&cub->player, -1);
	if (keys[ROT_R] && !keys[ROT_L])
		mv += rotate(&cub->player, 1);
	if ((keys[MOVE_F] && !keys[MOVE_B]) || (keys[MOVE_F_2] && !keys[MOVE_B_2]))
		mv += move(&cub->player, cub->map, 1);
	if ((keys[MOVE_B] && !keys[MOVE_F]) || (keys[MOVE_B_2] && !keys[MOVE_F_2]))
		mv += move(&cub->player, cub->map, -1);
	if (keys[STRAFE_L] && !keys[STRAFE_R])
		mv += strafe(&cub->player, cub->map, 1);
	if (keys[STRAFE_R] && !keys[STRAFE_L])
		mv += strafe(&cub->player, cub->map, -1);
	if (mv > 0)
	{
		check_borders(&cub->player, cub->map);
		draw_frame(cub);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->frame.img, 0, 0);
	}
	return (0);
}
