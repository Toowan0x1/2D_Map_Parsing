/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:05:51 by oel-houm          #+#    #+#             */
/*   Updated: 2022/10/13 11:04:00 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 7 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i++] - '0';
		if (res > LLONG_MAX && sign == -1)
			return (0);
		if (res > LLONG_MAX && sign == 1)
			return (-1);
	}
	return (res * sign);
}
