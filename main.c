/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:34:46 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:34:47 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void is_file_valid(char *str)
{
    int fd;

    fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        printf("[ERROR]: '%s' File not found.\n", str);
        exit (1);
    }
    close(fd);
    return ;
}

void check_file_existence_and_extension(char *file)
{
    int i;
    int index_to_start;

    i = 0;
    while (file[i])
        i++;
    index_to_start = i - 4;
    if (ft_strcmp(file + index_to_start, ".cub") == 0)
        is_file_valid(file);
    else
    {
        printf("[ERROR]: '.%s' Wrong file extention.\n", file + index_to_start);
        exit (1);
    }
}

int	calc_lines(int map_fd)
{
	int	i;

	i = 0;
	while (get_next_line(map_fd) != NULL)
		i++;
	close(map_fd);
	return (i);
}

void    read_and_store_map(char *map_name, t_map_info *map_data)
{
    char    *line;
    int     map_fd;
    int     i;
    
    map_fd = open(map_name, O_RDONLY);
    map_data->num_of_lines = calc_lines(map_fd);
    close(map_fd);
    map_data->map_content = (char **)malloc(sizeof(char *) * (map_data->num_of_lines + 1));
    i = 0;
    map_fd = open(map_name, O_RDONLY);;
    while ((line = get_next_line(map_fd)) != NULL)
    {
        map_data->map_content[i] = ft_strdup(line);
        remove_trailing_newline(map_data->map_content[i]);
        free(line);
        i++;
    }
    close(map_fd);
}



int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    t_map_info *map_data;
    map_data = malloc(sizeof(t_map_info));
    check_file_existence_and_extension(av[1]);
    read_and_store_map(av[1], map_data);
    init_map_line_ranges(map_data);
    sections_gaps_analysis(map_data);
    textures_parse(map_data);
    map_parse(map_data);
    show_info(map_data);
    printf(" => parsing success <=");
    return (0);
}