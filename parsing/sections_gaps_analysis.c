/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections_gaps_analysis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 01:11:47 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/07 01:11:48 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void    check_gaps(t_map_info *map_data, int start, int end)
{
    int i;

    while (start < end)
    {
        i = 0;
        while (map_data->map_content[start][i])
        {
            if (map_data->map_content[start][i] != 0)
            {
                printf("[ERROR]: Unexpected chracter '%c' found in the map at line %d index %d.\n", map_data->map_content[start][i], start+1, i);
                exit(1);
            }
            i++;
        }
        start++;
    }
}

void    start_texture_to_end_texture(char **map, int i, int end)
{
    while (map[i] && i < end)
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'C' && map[i][1] == ' ')
            i++;
        else if (map[i][0] == 'F' && map[i][1] == ' ')
            i++;
        else if (map[i][0] == 0)
            i++;
        else
        {
            printf("[ERROR]: Unexpected data found in the texture configuration at line %d. The entry '%s' is not recognized.\n", i + 1, map[i]);
            exit(1);
        }
    }
}

int    validate_characters(char c, int *character)
{
    if (c == 'N' || c == 'S' ||
        c == 'W' || c == 'E')
        (*character)++;
    if (c != '0' && c != '1' && 
        c != ' ' && c != '\t' &&
        c != 'N' && c != 'S' &&
        c != 'W' && c != 'E')
    {
        return (0);
    }
    return (1);
}

void    validate_player_chracter_count(int *character)
{
    if (*character > 1)
    {
        printf("[ERROR]: More than one character (player) detected on the map.\n");
        exit(1);
    }
    else if (*character == 0)
    {
        printf("[ERROR]: No character (player) found on the map.\n");
        exit(1);
    }
}

void    start_map_to_end_map(char **line, int start, int end)
{
    int i;
    int character;

    character = 0;
    while (start <= end)
    {
        i = 0;
        while (line[start][i])
        {
            if (validate_characters(line[start][i], &character) == 0)
            {
                printf("[ERROR]: Unexpected chracter '%c' found in the map at line %d index %d.", line[start][i], start + 1, i);
                exit(1);
            }
            i++;
        }
        start++;
    }
    validate_player_chracter_count(&character);
}

void sections_gaps_analysis(t_map_info *map_data)
{
    check_gaps(map_data, 0, map_data->texture_start_index); // start_to_end_texture
    start_texture_to_end_texture(map_data->map_content, map_data->texture_start_index, map_data->texture_end_index);
    check_gaps(map_data, map_data->texture_end_index + 1, map_data->map_start_index);
    check_gaps(map_data, map_data->map_end_index + 1, map_data->eof_index + 1);
    start_map_to_end_map(map_data->map_content, map_data->map_start_index, map_data->map_end_index);
}
