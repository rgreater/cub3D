/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:35:19 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/14 19:12:15 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map_size(t_list *lst, t_coords *size)
{
	t_list	*el;
	int		i;
	int		len;
	int		max_len;
	char	*str;

	if (!lst)
		return (-1);
	el = lst;
	i = 0;
	max_len = 0;
	while (el)
	{
		len = 0;
		str = el->content;
		while (str[len])
			len++;
		if (len > max_len)
			max_len = len;
		el = el->next;
		i++;
	}
	size->y = i;
	size->x = max_len;
	return (0);
}

void		load_map(t_cub *cub, t_list **list)
{
	int		i;
	t_list	*lst;

	lst = *list;
	if (get_map_size(lst, &cub->map_size) < 0)
		exit_err(cub, E_MAP, 0);
	if (cub->map_size.y < 3 || cub->map_size.x < 3)
		exit_err(cub, E_MAP, 0);
	lst = *list;
	if (!(cub->map = malloc(sizeof(char *) * (cub->map_size.y + 1))))
		exit_err(cub, 0, E_MAP_MALLOC);
	i = 0;
	while (i < cub->map_size.y)
	{
		cub->map[i++] = lst->content;
		lst = lst->next;
	}
	cub->map[i] = 0;
	ft_lstdestroy(list, 0);
	map_validation(cub);
}
