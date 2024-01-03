/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:28:35 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:30:48 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*************************************************************/
/*															 */
/*             T E X T U R E     P A R S I N G               */
/*															 */
/*************************************************************/

#include "../parsing.h"

void    check_number_of_texture(char **map)
{
    int i;
    int total_textures;
    
    total_textures = 0;
    i = 0;
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
            total_textures++;
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
            total_textures++;
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
            total_textures++;
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
            total_textures++;
        else if (map[i][0] == 'C' && map[i][1] == ' ')
            total_textures++;
        else if (map[i][0] == 'F' && map[i][1] == ' ')
            total_textures++;
        i++;
    }
    if (total_textures != 6)
    {
        write(2, "invalid number of textures.\n", 28);
        exit(1);
    }
}

//void    is_valid_color_range(char *str, t_map_info *map_data)
int    is_valid_color_range(char *str, t_map_info *map_data)
{
    int i;
    int res;

    res = 0;
    i = 0;
    (void)map_data;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
        {
            write(2, "*** invalid texture number ***\n", 31);
            exit(1);
        }
        i++;
    }
    while (str[i] && str[i] != ',')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            res *= 10;
            res += str[i] - '0';
        }
        else
        {
            write(2, "*** invalid texture number ***\n", 31);
            exit(1);
        }
        i++;
    }
    if (res > 255)
    {
        write(2, "*** texture number greather than 255 ***\n", 41);
        exit(1);
    }
    return (res);
}

void    is_valid_ceilling(t_map_info *map_data)
{
    int c_commas;
    int c_flag;
    int i;
    int c_index;

    c_commas = 0;
    c_flag = 0;
    i = 0;
    c_index = 0;
    while (map_data->ceiling[i])
    {
        if ((map_data->ceiling[i] >= '0' && map_data->ceiling[i] <= '9') ||
            (map_data->ceiling[i] == '+' || map_data->ceiling[i] == '-'))
        {
            if (c_flag == 0)
            {
                map_data->c_values[c_index] = is_valid_color_range(&map_data->ceiling[i], map_data);
                c_flag = 1;
                c_index++;
            }
        }
        else if (map_data->ceiling[i] == ',')
        {
            c_commas++;
            if (c_flag == 1)
                c_flag = 0;
        }
        else
        {
            write(2, "*** texture error ***\n", 22);
            exit(1);
        }
        i++;
    }
    if (c_commas != 2)
    {
        printf("invalid ceilling value\n");
        exit(1);
    }
}

void    is_valid_floor(t_map_info *map_data)
{
    int f_commas;
    int f_flag;
    int i;
    int f_index;

    f_commas = 0;
    f_flag = 0;
    i = 0;
    f_index = 0;
    while (map_data->floor[i])
    {
        if ((map_data->floor[i] >= '0' && map_data->floor[i] <= '9') ||
            (map_data->floor[i] == '+' || map_data->floor[i] == '-'))
        {
            if (f_flag == 0)
            {
                map_data->f_values[f_index] = is_valid_color_range(&map_data->floor[i], map_data);
                f_flag = 1;
                f_index++;
            }
        }
        else if (map_data->floor[i] == ',')
        {
            f_commas++;
            if (f_flag == 1)
                f_flag = 0;
        }
        else
        {
            write(2, "*** texture error ***\n", 22);
            exit(1);
        }
        i++;
    }
    if (f_commas != 2)
    {
        printf("invalid floor value\n");
        exit(1);
    }
}


// calc_rgb_color
void calc_color_value(t_map_info *map_data)
{
    int sum_c;
    int sum_f;
    int i;

    sum_c = 0;
    i = 0;
    while (i < (int)(sizeof(int) * 3) / (int)sizeof(int))
    {
        sum_c += map_data->c_values[i];
	    i++;
    }
    sum_f = 0;
    i = 0;
    while (i < (int)(sizeof(int) * 3) / (int)sizeof(int))
    {
        sum_f += map_data->f_values[i];
	    i++;
    }
    map_data->c_color = sum_c;
    map_data->f_color = sum_f;
}


void    textures_parse(t_map_info *map_data)
{
    check_number_of_texture(map_data->map_content);
    set_textures_values(map_data->map_content, map_data); // values of direction
    is_valid_ceilling(map_data);
    is_valid_floor(map_data);
    // function to set the 3 values and then calculate rgb

    calc_color_value(map_data);
}

// error: color value out of range 0 -> 255\n
