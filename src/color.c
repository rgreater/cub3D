/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 00:20:19 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 02:31:52 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_pixel_color(t_data *d, int x, int y)
{
	return (*(unsigned int *)
		(d->addr + y * d->line_length + x * d->bits_per_pixel));
}
