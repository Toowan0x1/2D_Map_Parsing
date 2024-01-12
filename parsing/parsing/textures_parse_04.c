/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_04.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:29:49 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/08 21:29:50 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	grab_numeric_value(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			printf("[ERROR]:dd Floor and ceiling values must be non-negative ");
			printf("and within 0 to 255 range.\n");
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
		i++;
	}
	return (res);
}

void	parse_individual_values(t_map_info *map_data, char attr, char *val)
{
	if (map_data->attr_flag == 0)
	{
		if (attr == 'f')
			map_data->f_values[map_data->attr_index] = grab_numeric_value(val);
		else if (attr == 'c')
			map_data->c_values[map_data->attr_index] = grab_numeric_value(val);
		map_data->attr_flag = 1;
		map_data->attr_index++;
	}
}

void	track_commas_and_disable_flag(t_map_info *map_data)
{
	map_data->attr_commas++;
	if (map_data->attr_flag == 1)
		map_data->attr_flag = 0;
}

static void	print_error(char attr)
{
	if (attr == 'f')
		printf("[ERROR]: Invalid provided value for Floor.\n");
	else if (attr == 'c')
		printf("[ERROR]: Invalid provided value for Ceilling.\n");
	exit(1);
}

void	is_valid_cf_attribute(t_map_info *map_data, char attr)
{
	int		i;
	char	*val;

	map_data->attr_commas = 0;
	map_data->attr_flag = 0;
	map_data->attr_index = 0;
	val = NULL;
	if (attr == 'f')
		val = map_data->floor;
	else if (attr == 'c')
		val = map_data->ceiling;
	i = 0;
	while (val[i])
	{
		if ((val[i] >= '0' && val[i] <= '9')
			|| (val[i] == '+' || val[i] == '-'))
			parse_individual_values(map_data, attr, &val[i]);
		else if (val[i] == ',')
			track_commas_and_disable_flag(map_data);
		else
			print_error(attr);
		i++;
	}
	if (map_data->attr_commas != 2)
		print_error(attr);
}
