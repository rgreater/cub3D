/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:12:16 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 18:08:51 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_draw_vals(t_sprite *s, t_cub *cub, t_coords *sprite)
{
	t_player *p;

	p = &cub->player;
	s->x = sprite->x + 0.50000 - p->x;
	s->y = sprite->y + 0.50000 - p->y;
	s->depth = s->inv_det * (s->x * -p->plane.y + s->y * p->plane.x);
	s->screen_x = round((cub->screen.width / 2.00) * (1.00 +
		s->inv_det * (s->x * p->dir.y - s->y * p->dir.x) / s->depth));
	s->height = round(cub->screen.height / s->depth * cub->screen.aspect_r);
	s->draw.y = cub->screen.height / 2 - s->height / 2;
	if (s->draw.y < 0)
		s->draw.y = 0;
	s->draw_end.y = cub->screen.height / 2 + s->height / 2;
	if (s->draw_end.y > cub->screen.height)
		s->draw_end.y = cub->screen.height;
	s->width = abs((int)(cub->screen.height / s->depth * cub->screen.aspect_r));
	s->width -= s->width % 2;
	s->draw.x = s->screen_x - s->width / 2;
	s->draw.x += s->draw.x % 2;
	if (s->draw.x < 0)
		s->draw.x = 0;
	s->draw_end.x = s->screen_x + s->width / 2;
	s->draw_end.x -= s->draw_end.x % 2;
	if (s->draw_end.x >= cub->screen.width)
		s->draw_end.x = cub->screen.width;
}

static void	draw_line(t_sprite *s, t_cub *cub, void *color_ptr, void *x_addr)
{
	void		*pxl;
	int			color;
	int			y;
	int			tex_y;
	t_texture	*sprite;

	sprite = &cub->texture.sprite;
	y = s->draw.y;
	while (y < s->draw_end.y)
	{
		tex_y = sprite->height * (2 * y + s->height - cub->screen.height) /
															(2 * s->height);
		color = *(unsigned int *)(color_ptr + tex_y * sprite->data.line_length);
		if (color > 0)
		{
			pxl = x_addr + y * cub->frame.line_length;
			*(unsigned int *)pxl = color;
		}
		y++;
	}
}

static void	draw_sprite(t_cub *c, t_sprite *s)
{
	t_texture	*sprite;
	int			tex_x;

	sprite = &c->texture.sprite;
	while (s->draw.x < s->draw_end.x)
	{
		if (s->depth < c->z_buf[s->draw.x])
		{
			tex_x = (int)((s->draw.x - (s->screen_x - s->width / 2.00)) *
										sprite->width / (double)s->width);
			draw_line(s, c, sprite->data.addr + tex_x *
				sprite->data.bits_per_pixel, c->frame.addr +
				(c->screen.width - 1 - s->draw.x) * c->frame.bits_per_pixel);
		}
		s->draw.x++;
	}
}

void		draw_sprites(t_cub *cub, t_player *p)
{
	t_sprite	s;
	int			i;

	quick_sort(cub->sprite, p, 0, cub->sprite_count - 1);
	s.inv_det = 1.00 / (p->plane.x * p->dir.y - p->plane.y * p->dir.x);
	i = cub->sprite_count - 1;
	while (i >= 0)
	{
		calc_draw_vals(&s, cub, &cub->sprite[i]);
		if (s.depth > 0.55)
			draw_sprite(cub, &s);
		i--;
	}
}
