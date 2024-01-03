/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_line_ranges.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:24:28 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:26:42 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*************************************************************/
/*															 */
/*         S E T    M A P   L I N E   R A N G E S            */
/*															 */
/*************************************************************/

#include "../parsing.h"

// int kmala(char *line)
// {
//     int j;
    
//     j = 0;
//     if (!line[j])
//         return (0);
//     while (line[j])
//     {
//         if (line[j] != '1' && line[j] != '0' && line[j] != ' ' && line[j] != '\t')
//             return 0; // Non-valid character found
//         j++;
//     }
//     return 1; // Valid line
// }

void    get_eof_index(t_map_info *map_data)
{
    int i;

    i = 0;
    while (map_data->map_content[i])
        map_data->eof_index = i++;
}

void    get_texture_first_line(t_map_info *map_data)
{
    int i;
    int total_textures;

    i = 0;
    total_textures = 0;
    while (map_data->map_content[i])
    {
        if (map_data->map_content[i][0] == 'N' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'S' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'W' && map_data->map_content[i][1] == 'E' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'E' && map_data->map_content[i][1] == 'A' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'C' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'F' && map_data->map_content[i][2] == ' ')
            total_textures++;
        if (total_textures > 0)
        {
            map_data->texture_start_index = i;
            break ;
        }
        i++;
    }
}

void    get_texture_last_line(t_map_info *map_data)
{
    int i;
    int total_textures;

    i = 0;
    total_textures = 0;
    while (map_data->map_content[i])
    {
        if (map_data->map_content[i][0] == 'N' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'S' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'W' && map_data->map_content[i][1] == 'E' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'E' && map_data->map_content[i][1] == 'A' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'C' && map_data->map_content[i][1] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'F' && map_data->map_content[i][1] == ' ')
            total_textures++;
        i++;
        if (total_textures == 6)
        {
            map_data->texture_end_index = i;
            break ;
        }
    }
}

int kmala(char *line)
{
    int j;
    
    j = 0;
    if (!line[j])
        return (0);
    while (line[j] && (line[j] == ' ' || line[j] == '\t'))
        j++;
        // if (line[j] != '1' && line[j] != '0' && line[j] != ' ' && line[j] != '\t')
        //     return 0; // Non-valid character found
        // j++;
    if (line[j] == '1')
    {
        return 1;
    }
    return 0;
}

void get_map_first_line(t_map_info *map_data)
{
    int i;

    i = 0;
    while (map_data->map_content[i])
    {
        if (kmala(map_data->map_content[i]))
        {
            map_data->map_start_index = i; // Found the first valid line, return its index
            return ;
        }
        i++;
    }
}

// void    get_map_last_line(t_map_info *map_data)
// {
//     int i;
    
//     i = map_data->map_start_index;
//     while (map_data->map_content[i])
//     {
//         if (!map_data->map_content[i])
//             break ;
//         if (map_data->map_content[i][0] == '1' && map_data->map_content[i][ft_strlen(map_data->map_content[i]) - 1] == '1')
//             map_data->map_end_index = i;
//         else if (map_data->map_content[i][0] == '1' && !map_data->map_content[i][1])
//             map_data->map_end_index = i;
//         //if (kmala2(line[i]))
//             //map_data->end_index = i;
//         //else
//             //map_data->end_index = i - 1;
//         i++;
//     }
// }

void    get_map_last_line(t_map_info *map_data)
{
    int i;
    int j;
    char **line;
    
    i = map_data->map_start_index;
    line = map_data->map_content;
    while (line[i])
    {
        if (!line[i] || (line[i][0] == 0 || line[i][0] == 10))
            break ;
        j = 0;
        while (line[i][j] && (line[i][j] == ' ' || line[i][j] == '\t'))
            j++;
        if (line[i][j] == '1' && line[i][ft_strlen(line[i]) - 1] == '1')
            map_data->map_end_index = i;
        else if (line[i][j] == '1' && !line[i][j + 1])
            map_data->map_end_index = i;
        i++;
    }
}

void    init_map_line_ranges(t_map_info *map_data)
{
    get_texture_first_line(map_data);
    get_texture_last_line(map_data);
    get_map_first_line(map_data);
    get_map_last_line(map_data);
    get_eof_index(map_data);
}
