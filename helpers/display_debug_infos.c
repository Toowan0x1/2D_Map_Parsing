/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_debug_infos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:33:23 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:33:44 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void    show_info(t_map_info *map_data)
{
    printf("\n");
    int index = map_data->texture_start_index;
    while (index <= map_data->map_end_index)
    {
        printf("i=%d=%s\n", index, map_data->map_content[index]);
        index++;
    }
    // printf("\n");
    // printf("textures start at index: %d\n", map_data->texture_start_index);
    // printf("textures end at index: %d\n", map_data->texture_end_index);
    // printf("map start at index: %d\n", map_data->map_start_index);
    // printf("map end at index: %d\n", map_data->map_end_index);
    // printf("map eof index: %d\n", map_data->eof_index);
    printf("\n ==> parsing successful <==\n");
}
