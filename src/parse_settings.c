/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:32:33 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 03:40:05 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_resolution(t_cub *cub, char *str, int *flag)
{
	t_screen	*s;

	if (*flag & 1)
		return (-1);
	s = &cub->screen;
	s->width = ft_atoi(&str);
	s->height = ft_atoi(&str);
	if (s->width <= 0 || s->height <= 0)
		return (-1);
	while (ft_isspace(*str))
		str++;
	if (*str)
		return (-1);
	*flag |= 1;
	return (0);
}

static int	set_texture_path(char **el, char *str, int *flag, int shift)
{
	int len;

	if (*flag >> shift & 1)
		return (-1);
	while (ft_isspace(*str))
		str++;
	len = ft_strlen(str) - 1;
	while (len > 0 && ft_isspace(str[len]))
		len--;
	if (len <= 0)
		return (-1);
	if (!(*el = malloc(sizeof(char) * (len + 2))))
		return (-2);
	ft_memmove(*el, str, len + 1);
	ft_memmove(*el + len + 1, "", 1);
	*flag |= 1 << shift;
	return (0);
}

static int	set_color(int *rgb, char **s, int pos)
{
	int		tmp;
	char	*str;

	str = *s;
	str++;
	while (ft_isspace(*str))
		str++;
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	tmp = ft_atoi(&str);
	if (tmp < 0 || tmp > 255)
		return (-1);
	while (ft_isspace(*str))
		str++;
	*rgb |= (tmp << pos);
	if (pos != 0 && *str != ',')
		return (-1);
	*s = str;
	return (0);
}

static int	set_colors(int *color, char *str, int *flag, int shift)
{
	if (*flag >> shift & 1)
		return (-1);
	*color = 0;
	if (set_color(color, &str, 16) < 0)
		return (-1);
	if (set_color(color, &str, 8) < 0)
		return (-1);
	if (set_color(color, &str, 0) < 0)
		return (-1);
	while (ft_isspace(*str))
		str++;
	if (*str)
		return (-1);
	*flag |= 1 << shift;
	return (0);
}

int			parse_settings(char *str, t_cub *cub, int *flag)
{
	int	err;

	err = -1;
	while (ft_isspace(*str))
		str++;
	if (*str == 'R' && !(*flag & 1))
		return (set_resolution(cub, str + 1, flag));
	else if (!ft_strncmp(str, "NO ", 3) && !(*flag >> 1 & 1))
		err = set_texture_path(&(cub->texture.n.path), str + 3, flag, 1);
	else if (!ft_strncmp(str, "SO ", 3) && !(*flag >> 2 & 1))
		err = set_texture_path(&(cub->texture.s.path), str + 3, flag, 2);
	else if (!ft_strncmp(str, "WE ", 3) && !(*flag >> 3 & 1))
		err = set_texture_path(&(cub->texture.w.path), str + 3, flag, 3);
	else if (!ft_strncmp(str, "EA ", 3) && !(*flag >> 4 & 1))
		err = set_texture_path(&(cub->texture.e.path), str + 3, flag, 4);
	else if (!ft_strncmp(str, "S ", 2) && !(*flag >> 5 & 1))
		err = set_texture_path(&(cub->texture.sprite.path), str + 2, flag, 5);
	else if (!ft_strncmp(str, "F ", 2) && !(*flag >> 6 & 1))
		return (set_colors(&(cub->color.floor), str, flag, 6));
	else if (!ft_strncmp(str, "C ", 2) && !(*flag >> 7 & 1))
		return (set_colors(&(cub->color.ceil), str, flag, 7));
	if (err == -2)
		exit_err(cub, 0, E_TEXPATH_MALLOC);
	return (err);
}
