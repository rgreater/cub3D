/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 01:58:18 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 14:01:34 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_strncmp(const char *s1, const char *s2, int n)
{
	int i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int		ft_strncmp_lcase(const char *s1, const char *s2, int n)
{
	int i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (ft_tolower(s1[i]) != ft_tolower(s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int		ft_strchr(char const c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}
