/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:51:18 by oel-houm          #+#    #+#             */
/*   Updated: 2022/10/13 05:26:32 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*x;

	i = 0;
	x = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!s || !f)
		return (NULL);
	if (!x)
		return (NULL);
	while (s[i])
	{
		x[i] = (*f)(i, s[i]);
		i++;
	}
	x[i] = '\0';
	return (x);
}
