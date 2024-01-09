/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section_detector_00.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:24:28 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/08 18:08:11 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	get_texture_first_line(t_map_info *map_data)
{
	int	i;
	int	total_textures;

	i = 0;
	total_textures = 0;
	while (map_data->map_content[i])
	{
		count_textures(map_data->map_content[i], &total_textures);
		if (total_textures > 0)
		{
			map_data->texture_start_index = i;
			break ;
		}
		i++;
	}
}

void	get_texture_last_line(t_map_info *map_data)
{
	int	i;
	int	total_textures;

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

void	get_map_first_line(t_map_info *map_data)
{
	int	i;

	i = 0;
	while (map_data->map_content[i])
	{
		if (is_line(map_data->map_content[i]))
		{
			map_data->map_start_index = i;
			return ;
		}
		i++;
	}
}

void	get_map_last_line(t_map_info *map_data)
{
	int		i;
	int		j;
	char	**line;

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

void	init_map_line_ranges(t_map_info *map_data)
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
	if (map_data->texture_start_index == -1 || map_data->texture_end_index == -1
		|| map_data->map_start_index == -1 || map_data->map_end_index == -1)
	{
		printf("[ERROR]: Map Error.\n");
		exit(1);
	}
}
