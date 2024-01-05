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
        printf("Error: '%s' File not found.\n", texture); // write error
        exit(1);
    }
    return ;
}

void    check_xpm_extension(char *texture)
{
    int i = 0;
    // function bohdha
    int flag = 0;
    if (texture[i] != '.')
        flag++;
    while (texture[i])
    {
        if (texture[i] == '.')
        {
            flag++;
            break;
        }
        i++;
    }
    if (texture[++i] != '.')
        flag++;
    if (flag != 3)
    {
        printf("[ERROR]: Invalid provided texture '%s'.\n", texture);
        exit(1);
    }
    // end hanaya
    i = 0;
    while (texture[i])
        i++;
    int index_to_start = i - 4;
    if (ft_strcmp(texture + index_to_start, ".xpm") == 0)
    {
        //is_valid(texture)
    }
    else {
        printf("[ERROR]: '%s' Wrong texture extension.\n", texture);
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
            if (!texture_split[1])
            {
                printf("[ERROR]: 'NO' attribute is not provided with a value.\n");
                exit(1);
            }
            if (texture_split[2])
            {
                printf("[ERROR]: Extra values found in the 'NO' attribute.\n");
                exit(1);
            }
            check_textures(map_data->no_texture);
            // if not xpm and if not valid
        }
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->so_texture = texture_split[1];
            if (!texture_split[1])
            {
                printf("[ERROR]: 'SO' attribute is not provided with a value.\n");
                exit(1);
            }
            if (texture_split[2])
            {
                printf("[ERROR]: Extra values found in the 'SO' attribute.\n");
                exit(1);
            }
            check_textures(map_data->so_texture);
        }
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->we_texture = texture_split[1];
            if (!texture_split[1])
            {
                printf("[ERROR]: 'WE' attribute is not provided with a value.\n");
                exit(1);
            }
            if (texture_split[2])
            {
                printf("[ERROR]: Extra values found in the 'WE' attribute.\n");
                exit(1);
            }
            check_textures(map_data->we_texture);
        }
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ea_texture = texture_split[1];
            if (!texture_split[1])
            {
                printf("[ERROR]: 'EA' attribute is not provided with a value.\n");
                exit(1);
            }
            if (texture_split[2])
            {
                printf("[ERROR]: Extra values found in the 'EA' attribute.\n");
                exit(1);
            }
            check_textures(map_data->ea_texture);
        }
        // check c and f
        else if (map[i][0] == 'C' && map[i][1] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ceiling = texture_split[1];
            if (!texture_split[1])
            {
                printf("[ERROR]: 'C' attribute is not provided with a value.\n");
                exit(1);
            }
            if (texture_split[2])
            {
                printf("[ERROR]: Extra values found in the 'C' attribute.\n");
                exit(1);
            }
        }
        else if (map[i][0] == 'F' && map[i][1] == ' ')
        {
            char **texture_split = ft_split(map[i], ' ');
            map_data->floor = texture_split[1];
            if (!texture_split[1])
            {
                printf("[ERROR]: 'F' attribute is not provided with a value.\n");
                exit(1);
            }
            if (texture_split[2])
            {
                printf("[ERROR]: Extra values found in the 'F' attribute.\n");
                exit(1);
            }
        }
        i++;
    }
}
