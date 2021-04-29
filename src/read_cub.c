/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 03:22:30 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/14 21:37:30 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	read_settings(t_cub *cub, int fd)
{
	int		flg_settings;
	int		lines_left;
	int		err;
	char	*line;

	err = 0;
	lines_left = 1;
	flg_settings = 0;
	while (flg_settings < 255 && lines_left)
	{
		if ((lines_left = get_next_line(fd, &line)) < 0)
		{
			close(fd);
			exit_err(cub, 0, E_GNL);
		}
		if (*line && err == 0)
			err += parse_settings(line, cub, &flg_settings);
		free(line);
	}
	if (lines_left == 0 || flg_settings < 255 || err != 0)
	{
		close(fd);
		exit_err(cub, E_READ_SETTINGS, 0);
	}
}

static int	read_map(int fd, t_list **lst)
{
	int		ret;
	int		err;
	char	*line;

	err = 0;
	while ((ret = get_next_line(fd, &line)) && !*line)
		free(line);
	while (ret && *line)
	{
		if (ft_lstadd_back(lst, ft_lstnew(line)) < 0)
			return (-3);
		if ((ret = get_next_line(fd, &line)) < 0)
			return (-2);
	}
	free(line);
	while ((ret = get_next_line(fd, &line)))
		if (*line)
			err = -1;
		else
			free(line);
	if (line)
		free(line);
	if (ret == -1)
		return (-2);
	return (err);
}

void		read_cubfile(t_cub *cub, char *filename)
{
	int			fd;
	t_list		*lst;
	int			ret;

	if (ft_strlen(filename) < 4 || ft_strncmp(
			filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
		exit_err(cub, E_WRONG_FILE_EXT, 0);
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit_err(cub, 0, filename);
	read_settings(cub, fd);
	lst = 0;
	ret = read_map(fd, &lst);
	close(fd);
	if (ret < 0)
	{
		ft_lstdestroy(&lst, 1);
		if (ret == -2)
			exit_err(cub, 0, E_GNL);
		else if (ret == -3)
			exit_err(cub, 0, "Map list");
		exit_err(cub, E_READ_SETTINGS, 0);
	}
	load_map(cub, &lst);
}
