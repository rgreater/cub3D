/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:41:23 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/09 17:12:11 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_val(t_coords sprite, int x, int y)
{
	return ((x - sprite.x) * (x - sprite.x) +
			(y - sprite.y) * (y - sprite.y));
}

static void	swap(t_coords *sprite_a, t_coords *sprite_b)
{
	t_coords tmp;

	tmp.x = sprite_a->x;
	tmp.y = sprite_a->y;
	sprite_a->x = sprite_b->x;
	sprite_a->y = sprite_b->y;
	sprite_b->x = tmp.x;
	sprite_b->y = tmp.y;
}

void		quick_sort(t_coords *arr, t_player *p, int start, int end)
{
	int l;
	int r;
	int pivot;

	l = start + 1;
	r = end;
	pivot = get_val(arr[start], p->x, p->y);
	if (start >= end)
		return ;
	while (l < r)
		if (get_val(arr[l], p->x, p->y) <= pivot)
			l++;
		else if (get_val(arr[r], p->x, p->y) >= pivot)
			r--;
		else
			swap(&arr[l], &arr[r]);
	if (get_val(arr[l], p->x, p->y) < pivot)
		swap(&arr[l--], &arr[start]);
	else
		swap(&arr[--l], &arr[start]);
	quick_sort(arr, p, start, l);
	quick_sort(arr, p, r, end);
}
