/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:13:51 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 18:19:19 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	select_texture(t_cub *cub, t_raycast *r, t_draw_tex *dt)
{
	int flip;

	flip = 0;
	if (r->side == NORTH)
	{
		flip = 1;
		dt->t = &cub->texture.n;
	}
	else if (r->side == EAST)
	{
		flip = 1;
		dt->t = &cub->texture.e;
	}
	else if (r->side == WEST)
		dt->t = &cub->texture.w;
	else
		dt->t = &cub->texture.s;
	return (flip);
}

static void	calc_draw_vals(t_draw_tex *dt, int screen_h, int line_h)
{
	dt->y = 0;
	dt->draw_start = screen_h / 2 - line_h / 2;
	if (dt->draw_start < 0)
	{
		dt->y = abs(dt->draw_start);
		dt->draw_start = 0;
	}
	dt->draw_end = screen_h / 2 + line_h / 2;
	if (dt->draw_end >= screen_h)
		dt->draw_end = screen_h;
	dt->step = (double)(dt->t->height) / (double)line_h;
}

static void	draw_wall(t_cub *cub, t_draw_tex *dt, void *data_ptr,
						void *color_ptr)
{
	void	*pxl;

	while (dt->draw_start < dt->draw_end)
	{
		pxl = data_ptr + dt->draw_start++ * cub->frame.line_length;
		*(unsigned int *)pxl = *(unsigned int *)
			(color_ptr + (int)(dt->y++ * dt->step) * dt->t->data.line_length);
	}
	if (dt->draw_end < cub->screen.height &&
		(int)(dt->y * dt->step) == dt->t->height)
	{
		pxl = data_ptr + (dt->draw_end - 1) * cub->frame.line_length;
		*(unsigned int *)pxl = *(unsigned int *)
			(color_ptr + (dt->t->height - 1) * dt->t->data.line_length);
	}
}

void		draw_texture(t_cub *cub, t_raycast *r, int screen_x)
{
	t_draw_tex	dt;
	void		*data_ptr;
	void		*color_ptr;
	int			tex_x;
	int			flip;

	flip = select_texture(cub, r, &dt);
	if (flip)
		tex_x = round(dt.t->width - 1 - r->wall_hit * (dt.t->width - 1));
	else
		tex_x = round(r->wall_hit * (dt.t->width - 1));
	calc_draw_vals(&dt, cub->screen.height, r->line_h);
	data_ptr = cub->frame.addr + (cub->screen.width - screen_x - 1) *
										cub->frame.bits_per_pixel;
	color_ptr = dt.t->data.addr + tex_x * dt.t->data.bits_per_pixel;
	draw_wall(cub, &dt, data_ptr, color_ptr);
}
