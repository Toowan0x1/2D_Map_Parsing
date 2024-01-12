/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:29:42 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/08 21:29:43 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	no(t_map_info *map_data, char **map, int i)
{
	char	**texture_split;

	texture_split = ft_split(map[i], ' ');
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
	check_xpm_extension(map_data->no_texture);
	check_texture_valid(map_data->no_texture);
}

void	so(t_map_info *map_data, char **map, int i)
{
	char	**texture_split;

	texture_split = ft_split(map[i], ' ');
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
	check_xpm_extension(map_data->so_texture);
	check_texture_valid(map_data->so_texture);
}

void	we(t_map_info *map_data, char **map, int i)
{
	char	**texture_split;

	texture_split = ft_split(map[i], ' ');
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
	check_xpm_extension(map_data->we_texture);
	check_texture_valid(map_data->we_texture);
}

void	ea(t_map_info *map_data, char **map, int i)
{
	char	**texture_split;

	texture_split = ft_split(map[i], ' ');
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
	check_xpm_extension(map_data->ea_texture);
	check_texture_valid(map_data->ea_texture);
}
void	f(t_map_info *map_data, char **map, int i)
{
	char	**texture_split;

	texture_split = ft_split(map[i], ' ');
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
