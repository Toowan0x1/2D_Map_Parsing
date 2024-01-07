/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_trailing_newline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:32:46 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:33:02 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void remove_trailing_newline(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}
