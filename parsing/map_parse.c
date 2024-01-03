/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:42:50 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:43:30 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*************************************************************/
/*															 */
/*                  M A P    P A R S I N G                   */
/*															 */
/*************************************************************/

#include "../parsing.h"

void    check_unsurrounded_zeros(char **line, int i)
{
    int j;

    j = 0;
    while (line[i][j])
    {
        if (line[i][j] == ' ')
        {
            if (line[i - 1][j] == '0' || line[i + 1][j] == '0')
            {
                printf("MAP ERROR: Unsurrounded 0 detected in line %d\n", i + 1);
                exit(1);
            }
        }
        else if (line[i][j] == '0')
        {
            if ((line[i - 1][j] == ' ' || line[i + 1][j] == ' ') ||
                (j > (int)ft_strlen(line[i - 1]) - 1 || j > (int)ft_strlen(line[i + 1]) - 1) ||
                (line[i][j - 1] == ' ' || line[i][j + 1] == ' '))
            {
                printf("MAP ERROR: Unsurrounded 0 detected in line %d\n", i + 1);
                exit(1);
            }
        }
        j++;
    }
    /* Check Edges */
    // check edges: last char
    if (line[i][ft_strlen(line[i] + 1)] != '1')
    {
        printf("last chracter f line %d is not 1\n", i + 1);
        exit(1);
    }
    // check edges: first char
    j = 0;
    while (line[i][j] && (line[i][j] == ' ' || line[i][j] == '\t'))
        j++;
    if (line[i][j] != '1')
    {
        printf("first chracter f line %d is not 1.\n", i + 1);
        exit(1);
    }
}

// check the first and last map's line if it's surounded only by ones 11111111
void    check_surrounded_by_ones(char *line)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ' && line[i] != '\t')
        {
            printf("MAP ERROR: The first or last line is not fully enclosed by walls.\n");
            exit(1);
        }
        i++;
    }
}

void    map_parse(t_map_info *map_data)
{
    int i;

    i = map_data->map_start_index;
    while (map_data->map_content[i] && i <= map_data->map_end_index)
    {
        if (i == map_data->map_start_index)
            check_surrounded_by_ones(map_data->map_content[map_data->map_start_index]);
        else if (i > map_data->map_start_index && i < map_data->map_end_index)
            check_unsurrounded_zeros(map_data->map_content, i);
        else if (i == map_data->map_end_index)
            check_surrounded_by_ones(map_data->map_content[map_data->map_end_index]);
        i++;
    }
}
