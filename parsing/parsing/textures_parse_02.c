/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:41:18 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/08 17:57:22 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	c(t_map_info *map_data, char **map, int i)
{
	char	**texture_split;

	texture_split = ft_split(map[i], ' ');
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

void	examine_texture_format(char *texture)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (texture[i] != '.')
		flag++;
	while (texture[i])
	{
		if (texture[i] == '.')
		{
			flag++;
			break ;
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
}

void	check_xpm_extension(char *texture)
{
	int	i;
	int	index_to_start;

	i = 0;
	examine_texture_format(texture);
	while (texture[i])
		i++;
	index_to_start = i - 4;
	if (!(ft_strcmp(texture + index_to_start, ".xpm") == 0))
	{
		printf("[ERROR]: '%s' Wrong texture extension.\n", texture);
		exit(1);
	}
}

void	check_texture_valid(char *texture)
{
	if (access(texture, F_OK) != 0)
	{
		printf("[Error]: '%s' File not found.\n", texture);
		exit(1);
	}
	return ;
}

void	set_textures_values(char **map, t_map_info *map_data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
			no(map_data, map, i);
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
			so(map_data, map, i);
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
			we(map_data, map, i);
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
			ea(map_data, map, i);
		else if (map[i][0] == 'C' && map[i][1] == ' ')
			c(map_data, map, i);
		else if (map[i][0] == 'F' && map[i][1] == ' ')
			f(map_data, map, i);
		i++;
	}
}
