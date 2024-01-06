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

#include "../parsing.h"

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
        else if (map_data->map_content[i][0] == 'C' && map_data->map_content[i][1] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'F' && map_data->map_content[i][1] == ' ')
            total_textures++;
        if (total_textures > 0)
        {
            map_data->texture_start_index = i;
            break ;
        }
        i++;
    }
}

void    count_total_textures(char **map, t_map_info *map_data);

void    until_last_textures(char *lolo, int *total_textures)
{
    if (lolo[0] == 'N' && lolo[1] == 'O' && lolo[2] == ' ')
        (*total_textures)++;
    else if (lolo[0] == 'S' && lolo[1] == 'O' && lolo[2] == ' ')
        (*total_textures)++;
    else if (lolo[0] == 'W' && lolo[1] == 'E' && lolo[2] == ' ')
        (*total_textures)++;
    else if (lolo[0] == 'E' && lolo[1] == 'A' && lolo[2] == ' ')
        (*total_textures)++;
    else if (lolo[0] == 'C' && lolo[1] == ' ')
        (*total_textures)++;
    else if (lolo[0] == 'F' && lolo[1] == ' ')
        (*total_textures)++;
}

void    get_texture_last_line(t_map_info *map_data)
{
    int i;
    int total_textures;

    i = 0;
    total_textures = 0;
    count_total_textures(map_data->map_content, map_data);
    while (map_data->map_content[i])
    {
        until_last_textures(map_data->map_content[i], &total_textures);
        if (total_textures == 6)
        {
            map_data->texture_end_index = i;
            break ;
        }
        i++;
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
    if (line[j] == '1')
        return 1;
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
            map_data->map_start_index = i;
            return ;
        }
        i++;
    }
}

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
    map_data->texture_start_index = -1;
    map_data->texture_end_index = -1;
    map_data->map_start_index = -1;
    map_data->map_end_index = -1;
    get_texture_first_line(map_data);
    get_texture_last_line(map_data);
    get_map_first_line(map_data);
    get_map_last_line(map_data);
    get_eof_index(map_data);
    if (map_data->texture_start_index == -1 || map_data->texture_end_index == -1 ||
        map_data->map_start_index == -1 || map_data->map_end_index == -1)
    {
        printf("[ERROR]: Map Error.\n");
        exit(1);
    }
}
