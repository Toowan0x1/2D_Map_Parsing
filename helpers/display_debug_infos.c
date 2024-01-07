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

//void      cf_data + calculation
//void      textures
//void      map

void    show_info(t_map_info *map_data)
{
    printf("\n");
    int index = map_data->texture_start_index;
    while (index <= map_data->map_end_index)
    {
        printf("i=%d=%s\n", index + 0, map_data->map_content[index]);
        index++;
    }
    printf("\n");
    printf("textures start at index: %d\n", map_data->texture_start_index);
    printf("textures end at index: %d\n", map_data->texture_end_index);
    printf("map start at index: %d\n", map_data->map_start_index);
    printf("map end at index: %d\n", map_data->map_end_index);
    printf("map eof index: %d\n", map_data->eof_index);

    /* display extracted fc data: */
    
    // printf("\n\n");
    // printf("ceilling values are:\t%d,%d,%d\n", map_data->c_values[0], map_data->c_values[1], map_data->c_values[2]);
    // printf("ceilling color is:\t%d", map_data->c_color);
    // printf("\n");
    // printf("floor values are:\t%d,%d,%d\n", map_data->f_values[0], map_data->f_values[1], map_data->f_values[2]);
    // printf("floor color is:\t\t%d", map_data->f_color);

    //index 0 to first line texture
    // printf("%d -> %d\n", 0+1, map_data->texture_start_index+1);
    // last line texture to first line map
    // printf("%d -> %d\n", map_data->texture_end_index+1, map_data->map_start_index+1);
    // last line map to eof index
    // printf("%d -> %d\n", map_data->map_end_index+1, map_data->eof_index+1);
    
    // printf("\n ==> parsing successful <==\n");
}
