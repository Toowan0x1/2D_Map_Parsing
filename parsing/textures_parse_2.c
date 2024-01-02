/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:41:18 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:41:49 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void    check_texture_valid(char *texture)
{
    if (access(texture, F_OK) != 0)
    {
        printf("File not found.\n"); // write error
        exit(1);
    }
    return ;
}

void    check_xpm_extension(char *texture)
{
    int i = 0;
    while (texture[i])
        i++;
    int index_to_start = i - 4;
    if (ft_strcmp(texture + index_to_start, ".xpm") == 0)
    {
        //is_valid(texture)
    }
    else {
        write(2, "wrong texture extension.\n", 26);
        exit(1);
    }
}

void    check_textures(char *texture)
{
    check_xpm_extension(texture);
    check_texture_valid(texture);
}

void    set_textures_values(char **map, t_map_info *map_data)
{
    int i;
    i = 0;
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->no_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->no_texture);
            // if not xpm and if not valid
        }
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->so_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->so_texture);
        }
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->we_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->we_texture);
        }
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ea_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->ea_texture);
        }
        // check c and f
        else if (map[i][0] == 'C' && map[i][1] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ceiling = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
        }
        else if (map[i][0] == 'F' && map[i][1] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->floor = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
        }
        i++;
    }
}
