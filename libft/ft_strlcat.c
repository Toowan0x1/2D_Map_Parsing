/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 06:23:18 by oel-houm          #+#    #+#             */
/*   Updated: 2022/10/11 01:49:05 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (!dst || size == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (size <= dstlen)
		srclen += size;
	else
		srclen += dstlen;
	while (src[i] && (dstlen + 1 < size))
	{
		dst[dstlen] = src[i];
		dstlen++;
		i++;
	}
	if (size > dstlen)
		dst[dstlen] = '\0';
	return (srclen);
}
