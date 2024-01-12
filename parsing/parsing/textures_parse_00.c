/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:29:32 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/08 21:29:35 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	init_textures_value(t_map_info *map_data)
{
	map_data->c_total = 0;
	map_data->f_total = 0;
	map_data->no_total = 0;
	map_data->so_total = 0;
	map_data->ea_total = 0;
	map_data->we_total = 0;
}

void	validate_texture_count(t_map_info *map_data)
{
	if (!(map_data->c_total == 1 && map_data->f_total == 1
			&& map_data->no_total == 1 && map_data->so_total == 1
			&& map_data->ea_total == 1 && map_data->we_total == 1))
	{
		printf("[ERROR]: ");
		printf("Incorrect number of textures provided. ");
		printf("Please ensure that the correct number of textures is ");
		printf("specified for each attribute ");
		printf("(e.g., 'F', 'C', 'WE', 'NO', 'SO', 'EA').\n");
		exit(1);
	}
}

void	count_total_textures(char **map, t_map_info *map_data)
{
	int	i;

	i = 0;
	init_textures_value(map_data);
	while (map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
			map_data->no_total++;
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
			map_data->so_total++;
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
			map_data->we_total++;
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
			map_data->ea_total++;
		else if (map[i][0] == 'C' && map[i][1] == ' ')
			map_data->c_total++;
		else if (map[i][0] == 'F' && map[i][1] == ' ')
			map_data->f_total++;
		i++;
	}
	validate_texture_count(map_data);
}

void	textures_parse(t_map_info *map_data)
{
	count_total_textures(map_data->map_content, map_data);
	init_cf_values(map_data);
	set_textures_values(map_data->map_content, map_data);
	is_valid_cf_attribute(map_data, 'c');
	is_valid_cf_attribute(map_data, 'f');
	validate_cf_errors(map_data);
	calc_cf_color_value(map_data);
}
