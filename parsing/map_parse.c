/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:42:50 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/08 16:37:08 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	check_surrounded_by_ones(char *line, int n)
{
	int	i;

	if ((line[(int)ft_strlen(line) - 1]) != '1')
	{
		if ((line[(int)ft_strlen(line) - 1]) == '0')
		{
			printf("[ERROR]: ");
			printf("The line %d is not fully enclosed by walls.\n", n + 1);
		}
		else if ((line[(int)ft_strlen(line) - 1]) == ' ')
			printf("[ERROR]: Found extra spaces in line %d\n", n + 1);
		exit(1);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\t')
		{
			printf("ERROR: ");
			printf("The first or last line is not fully enclosed by walls.\n");
			exit(1);
		}
		i++;
	}
}

void	check_unsurrounded_edges(char **line, int i)
{
	int	j;

	j = 0;
	if (line[i][ft_strlen(line[i] + 1)] != '1')
	{
		if (line[i][ft_strlen(line[i] + 1)] == '0')
		{
			printf("[ERROR]: ");
			printf("The line %d is not fully enclosed by walls.\n", i + 1);
		}
		else if (line[i][ft_strlen(line[i] + 1)] == ' ')
			printf("[ERROR]: Found extra spaces in line %d.\n", i + 1);
		exit(1);
	}
	j = 0;
	while (line[i][j] && (line[i][j] == ' ' || line[i][j] == '\t'))
		j++;
	if (line[i][j] != '1')
	{
		printf("[ERROR]: Unsurrounded 0 detected in line %d\n", i + 1);
		exit(1);
	}
}

static void	print_error(int i)
{
	printf("[ERROR]: Unsurrounded 0 detected in line %d\n", i + 1);
	exit(1);
}

void	check_unsurrounded_zeros(char **line, int i)
{
	int	j;

	j = 0;
	while (line[i][j])
	{
		if (line[i][j] == ' ')
		{
			if ((line[i - 1][j] == '0' || line[i + 1][j] == '0') &&
					!(j > (int)ft_strlen(line[i + 1])) &&
					!(j > (int)ft_strlen(line[i - 1])))
				print_error(i);
		}
		else if (line[i][j] == '0')
		{
			if ((line[i - 1][j] == ' ' || line[i + 1][j] == ' ') || (
					j > (int)ft_strlen(line[i - 1]) - 1 ||
					j > (int)ft_strlen(line[i + 1]) - 1) ||
					(line[i][j - 1] == ' ' || line[i][j + 1] == ' '))
				print_error(i);
		}
		j++;
	}
}

void	map_parse(t_map_info *map_data)
{
	int	i;

	i = map_data->map_start_index;
	while (map_data->map_content[i] && i <= map_data->map_end_index)
	{
		if (i == map_data->map_start_index)
			check_surrounded_by_ones(
				map_data->map_content[map_data->map_start_index], i);
		else if (i > map_data->map_start_index && i < map_data->map_end_index)
		{
			check_unsurrounded_edges(map_data->map_content, i);
			check_unsurrounded_zeros(map_data->map_content, i);
		}
		else if (i == map_data->map_end_index)
			check_surrounded_by_ones(
				map_data->map_content[map_data->map_end_index], i);
		i++;
	}
}
