/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:16:15 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 15:30:54 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_half(t_data *frame, int width, int limit, int color)
{
	char	*pxl;
	char	*start;
	int		y;
	int		x;

	y = 0;
	while (y < limit)
	{
		start = frame->addr + y * frame->line_length;
		x = 0;
		while (x < width)
		{
			pxl = start + x * frame->bits_per_pixel;
			*(unsigned int *)pxl = color;
			x++;
		}
		y++;
	}
	return (y);
}

void		draw_bg(t_screen *s, t_data *frame, t_color *color)
{
	int		x;
	int		y;
	char	*pxl;
	char	*start;

	y = draw_half(frame, s->width, s->height / 2, color->ceil);
	while (y < s->height)
	{
		start = frame->addr + y * frame->line_length;
		x = 0;
		while (x < s->width)
		{
			pxl = start + x * frame->bits_per_pixel;
			*(unsigned int *)pxl = color->floor;
			x++;
		}
		y++;
	}
}
