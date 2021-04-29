/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 03:18:56 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/15 00:29:12 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	show_hint(char *exec_name)
{
	printf("  \033[1m%s\e[0m \e[4mmap\e[0m [--save]\n", exec_name);
	printf("    \e[4mmap\e[0m\n\t\t  Run cub3D in regular mode.\n");
	printf("    \e[4mmap\e[0m --save\n\t\t  Save image in bmp format.\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc == 3 && !ft_strncmp(argv[2], "--save", 6) &&
								ft_strlen(argv[2]) == 6)
		load_cub(&cub, argv[1], SAVE_BMP);
	else if (argc != 2)
		return (show_hint(argv[0]));
	load_cub(&cub, argv[1], REG_MODE);
	mlx_hook(cub.window, 2, 1L, key_down, &cub);
	mlx_hook(cub.window, 3, 1L << 1, key_up, &cub);
	mlx_hook(cub.window, 17, 0L, exit_clean, &cub);
	mlx_loop_hook(cub.mlx, move_player, &cub);
	mlx_loop(cub.mlx);
	return (exit_clean(&cub));
}
