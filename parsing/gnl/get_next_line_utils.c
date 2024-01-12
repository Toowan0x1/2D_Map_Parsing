/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 21:22:55 by oel-houm          #+#    #+#             */
/*   Updated: 2022/10/30 00:15:35 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (*s1)
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (&str[i]);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*x;

	slen = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (len >= slen)
		len = slen;
	x = (char *)malloc(sizeof(char) * (len + 1));
	if (x == NULL)
		return (NULL);
	i = 0;
	if (slen > start)
	{
		while (i < len)
		{
			x[i] = s[start];
			start++;
			i++;
		}
	}
	x[i] = '\0';
	return (x);
}
