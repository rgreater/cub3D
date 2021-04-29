/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:54:08 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/14 23:17:04 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	hex_tostring(char *str, unsigned int num)
{
	str[0] = num & 0xFF;
	str[1] = (num >> 8) & 0xFF;
	str[2] = (num >> 16) & 0xFF;
	str[3] = (num >> 24) & 0xFF;
}

static char	*create_bmp_string(int img_width, int img_height, unsigned int len)
{
	char			*str;

	if (!(str = malloc(sizeof(char) * len)))
		return (0);
	ft_memmove(str, "\x42\x4D", 2);
	hex_tostring(str + 2, len);
	ft_memmove(str + 6, BMP_HDR_START, 12);
	hex_tostring(str + 18, img_width);
	hex_tostring(str + 22, img_height);
	ft_memmove(str + 26, BMP_HDR_E, 28);
	return (str);
}

static void	fill_bmp_string(char *str, int row_width, t_cub *cub)
{
	int		x;
	int		y;
	int		i;
	int		color;
	char	*str_ptr;

	y = cub->screen.height - 1;
	while (y >= 0)
	{
		x = 0;
		str_ptr = str + row_width * (cub->screen.height - 1 - y);
		while (x < cub->screen.width)
		{
			color = get_pixel_color(&cub->frame, x, y);
			str_ptr[x * 3] = color & 0xFF;
			str_ptr[x * 3 + 1] = (color >> 8) & 0xFF;
			str_ptr[x * 3 + 2] = color >> 16;
			x++;
		}
		i = 0;
		while (x * 3 + i < row_width)
			str_ptr[x * 3 + i++] = 0;
		y--;
	}
}

static int	str_tofile(char *name, char *str, unsigned int len)
{
	int		fd;
	char	*filename;

	if (!(filename = malloc(sizeof(char) * (ft_strlen(name) + 1))))
		return (-1);
	ft_memmove(filename, name, ft_strlen(name) + 1);
	ft_memmove(filename + ft_strlen(name) - 3, "bmp", 3);
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(filename);
	if (fd < 0)
		return (-2);
	write(fd, str, len);
	close(fd);
	return (0);
}

int			save_bmp(t_cub *cub, char *map_name)
{
	char			*str;
	int				row_width;
	unsigned int	len;
	int				ret;

	draw_frame(cub);
	row_width = cub->screen.width * 3 + cub->screen.width % 4;
	len = row_width * cub->screen.height + 54;
	if (!(str = create_bmp_string(cub->screen.width, cub->screen.height, len)))
		exit_err(cub, 0, E_BMP_STRING);
	fill_bmp_string(str + 54, row_width, cub);
	ret = str_tofile(map_name, str, len);
	free(str);
	if (ret == -1)
		exit_err(cub, 0, E_BMP_STRING);
	else if (ret == -2)
		exit_err(cub, 0, E_BMP_FILE);
	return (exit_clean(cub));
}
