/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:28:35 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/08 17:33:32 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	init_cf_values(t_map_info *map_data)
{
	map_data->c_values = (int *)malloc(sizeof(int) * 3);
	map_data->f_values = (int *)malloc(sizeof(int) * 3);
	map_data->c_values[0] = -1;
	map_data->c_values[1] = -1;
	map_data->c_values[2] = -1;
	map_data->f_values[0] = -1;
	map_data->f_values[1] = -1;
	map_data->f_values[2] = -1;
}

void	calc_cf_color_value(t_map_info *map_data)
{
	int	sum_c;
	int	sum_f;
	int	i;

	sum_c = 0;
	i = 0;
	while (i < ((int) sizeof(int) * 3 / (int) sizeof(int)))
	{
		sum_c += map_data->c_values[i];
		i++;
	}
	sum_f = 0;
	i = 0;
	while (i < ((int) sizeof(int) * 3 / (int) sizeof(int)))
	{
		sum_f += map_data->f_values[i];
		i++;
	}
	map_data->c_color = sum_c;
	map_data->f_color = sum_f;
}

void	validate_cf_errors(t_map_info *map_data)
{
	if (map_data->c_values[2] == -1)
	{
		printf("[ERROR]: Invalid provided value for Ceilling.\n");
		exit(1);
	}
	if (map_data->f_values[2] == -1)
	{
		printf("[ERROR]: Invalid provided value for Floor.\n");
		exit(1);
	}
	if (map_data->c_values[0] > 255 || map_data->c_values[1] > 255
		|| map_data->c_values[2] > 255)
	{
		printf("[ERROR]: Floor and ceiling values must not exceed 255, ");
		printf("and should be within the range of 0 to 255.\n");
		exit(1);
	}
	if (map_data->f_values[0] > 255 || map_data->f_values[1] > 255
		|| map_data->f_values[2] > 255)
	{
		printf("[ERROR]: Floor and ceiling values must not exceed 255, ");
		printf("and should be within the range of 0 to 255..\n");
		exit(1);
	}
}