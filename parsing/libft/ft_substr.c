/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 05:36:02 by oel-houm          #+#    #+#             */
/*   Updated: 2022/10/09 15:38:20 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*str;

	size = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (len >= size)
		len = size;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (start < size)
	{
		while (i < len)
		{
			str[i] = s[start];
			start++;
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
