/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:09:00 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 14:58:59 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_init_vals(t_player *p, t_raycast *r, int screen_width, int x)
{
	r->ray_pos = 2 * x / (double)screen_width - 1;
	r->raydir.x = p->dir.x + p->plane.x * r->ray_pos;
	r->raydir.y = p->dir.y + p->plane.y * r->ray_pos;
	r->map.x = p->x;
	r->map.y = p->y;
	r->ddist.x = fabs(1 / r->raydir.x);
	r->ddist.y = fabs(1 / r->raydir.y);
	r->inc.x = (r->raydir.x < 0) ? -1 : 1;
	r->inc.y = (r->raydir.y < 0) ? -1 : 1;
	r->sidedist.x = (r->raydir.x < 0) ? (p->x - r->map.x) * r->ddist.x :
								(r->map.x + 1 - p->x) * r->ddist.x;
	r->sidedist.y = (r->raydir.y < 0) ? (p->y - r->map.y) * r->ddist.y :
								(r->map.y + 1 - p->y) * r->ddist.y;
}

static void	cast_ray(char **map, t_player *p, t_raycast *r)
{
	while (map[r->map.y][r->map.x] != '1')
		if (r->sidedist.x < r->sidedist.y)
		{
			r->sidedist.x += r->ddist.x;
			r->map.x += r->inc.x;
			r->side = (p->x < r->map.x) ? WEST : EAST;
		}
		else
		{
			r->sidedist.y += r->ddist.y;
			r->map.y += r->inc.y;
			r->side = (p->y < r->map.y) ? NORTH : SOUTH;
		}
}

static void	calc_draw_vals(t_cub *cub, t_raycast *r, int x)
{
	t_player *p;

	p = &cub->player;
	if (r->side < 2)
	{
		r->wall_dist = (r->map.x - p->x + (1 - r->inc.x) / 2) / r->raydir.x;
		r->wall_hit = p->y + r->wall_dist * r->raydir.y;
	}
	else
	{
		r->wall_dist = (r->map.y - p->y + (1 - r->inc.y) / 2) / r->raydir.y;
		r->wall_hit = p->x + r->wall_dist * r->raydir.x;
	}
	if (cub->sprite_count > 0)
		cub->z_buf[x] = r->wall_dist;
	r->wall_hit = modf(r->wall_hit, &r->wall_hit);
	r->line_h = cub->screen.height / r->wall_dist * cub->screen.aspect_r;
	r->line_h += r->line_h % 2;
}

void		draw_frame(t_cub *cub)
{
	t_raycast	r;
	int			x;

	draw_bg(&cub->screen, &cub->frame, &cub->color);
	x = 0;
	while (x < cub->screen.width)
	{
		calc_init_vals(&cub->player, &r, cub->screen.width, x);
		cast_ray(cub->map, &cub->player, &r);
		calc_draw_vals(cub, &r, x);
		draw_texture(cub, &r, x);
		x++;
	}
	if (cub->sprite_count > 0)
		draw_sprites(cub, &cub->player);
}
