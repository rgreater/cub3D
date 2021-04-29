/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:02:26 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 14:32:35 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRMSG_H
# define ERRMSG_H
# ifndef ERROR
#  define ERROR "Error\n"
# endif
# ifndef E_WRONG_FILE_EXT
#  define E_WRONG_FILE_EXT "Invalid configuration file extension.\n"
# endif
# ifndef E_WIN_TITLE
#  define E_WIN_TITLE "Window title string"
# endif
# ifndef E_GNL
#  define E_GNL "The file couldn't be read properly"
# endif
# ifndef E_READ_SETTINGS
#  define E_READ_SETTINGS "Your .cub file is incorrectly configured. RTFM!\n"
# endif
# ifndef E_TEXPATH_MALLOC
#  define E_TEXPATH_MALLOC "Texture path"
# endif
# ifndef E_MAP_MALLOC
#  define E_MAP_MALLOC "Map"
# endif
# ifndef E_MAP
#  define E_MAP "Invalid map.\n"
# endif
# ifndef E_MAP_PLAYER
#  define E_MAP_PLAYER "Invalid map: none or too many starting points.\n"
# endif
# ifndef E_MAP_CHAR
#  define E_MAP_CHAR "Invalid character inside the map.\n"
# endif
# ifndef E_SPRITE_MALLOC
#  define E_SPRITE_MALLOC "Sprites"
# endif
# ifndef E_MLX_INIT
#  define E_MLX_INIT "MLX initialization failure.\n"
# endif
# ifndef E_MLX_IMG
#  define E_MLX_IMG "Couldn't create a MLX image.\n"
# endif
# ifndef E_MLX_ADDR
#  define E_MLX_ADRR "Couldn't get the address of a MLX image.\n"
# endif
# ifndef E_MLX_WIN
#  define E_MLX_WIN "Couldn't create a window.\n"
# endif
# ifndef E_BMP_FILE
#  define E_BMP_FILE "Couldn't open/create .bmp file"
# endif
# ifndef E_BMP_STRING
#  define E_BMP_STRING "Unable to create bmp file string"
# endif
# ifndef E_PNG
#  define E_PNG "This cub3D doesn't support .PNG textures, please use .XPM.\n"
# endif
# ifndef E_TEX_FILEXT
#  define E_TEX_FILEXT "Invalid texture file(s) extension, should be .XPM.\n"
# endif

#endif
