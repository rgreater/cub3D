/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 03:08:03 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 03:39:27 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(char **line)
{
	unsigned int	num;
	char			*str;

	str = *line;
	num = 0;
	while (ft_isspace(*str))
		str++;
	while ((*str >= '0') && (*str <= '9') && num <= 1000000)
	{
		num = num * 10 + *str - 48;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
		str++;
	*line = str;
	return ((int)num);
}

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return ((unsigned int)(-n));
	return ((unsigned int)n);
}

static int			ft_getlen(unsigned int n)
{
	int				len;
	unsigned int	num;

	len = 0;
	num = n;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	if (len == 0)
		len = 1;
	return (len);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;
	unsigned int	num;

	sign = 0;
	if (n < 0)
		sign = 1;
	num = ft_abs(n);
	len = ft_getlen(num) + sign;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len--] = 0;
	while (len >= 0 + sign)
	{
		str[len] = num % 10 + 48;
		len--;
		num = num / 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
