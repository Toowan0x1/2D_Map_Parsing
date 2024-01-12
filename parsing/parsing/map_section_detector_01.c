/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section_detector_01.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:18:05 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/09 00:18:07 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"


void	get_eof_index(t_map_info *map_data)
{
	int	i;

	i = 0;
	while (map_data->map_content[i])
		map_data->eof_index = i++;
}

void	count_textures(char *line, int *total_textures)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'C' && line[1] == ' ')
		(*total_textures)++;
	else if (line[0] == 'F' && line[1] == ' ')
		(*total_textures)++;
}

void	until_last_textures(char *line, int *total_textures)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		(*total_textures)++;
	else if (line[0] == 'C' && line[1] == ' ')
		(*total_textures)++;
	else if (line[0] == 'F' && line[1] == ' ')
		(*total_textures)++;
}

int	is_line(char *line)
{
	int	j;

	j = 0;
	if (!line[j])
		return (0);
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] == '1')
		return (1);
	return (0);
}

