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
        printf("'%s': File not found.\n", str);
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
        printf("'.%s': Wrong file extention.\n", file + index_to_start);
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
        //map_data->map_content[i] = malloc(sizeof(char) * ft_strlen(line) + 1);
        map_data->map_content[i] = ft_strdup(line);
        remove_trailing_newline(map_data->map_content[i]);
        free(line);
        i++;
    }
    close(map_fd);
}

void    check_gaps(t_map_info *map_data, int start, int end)
{
    int i;

    while (start < end)
    {
        i = 0;
        while (map_data->map_content[start][i])
        {
            if (map_data->map_content[start][i] != 0)
            {
                printf("Error in line %d\n", start + 1);
                exit(1);
            }
            i++;
        }
        start++;
    }
}

void    check_0_to_end_texture(char **map, int i, int end)
{
    while (map[i] && i < end)
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
            i++;
        else if (map[i][0] == 'C' && map[i][1] == ' ')
            i++;
        else if (map[i][0] == 'F' && map[i][1] == ' ')
            i++;
        else if (map[i][0] == 0)
            i++;
        else
        {
            printf("something found between 0 and end textures in line %d\n", i+1);
            exit(1);
        }
    }
}

// this func name must be changed (according to to code functionality)
void    has_gap_between_lines(char **line, int start, int end)
{
    int i;
    int character;

    character = 0;
    while (start <= end)
    {
        i = 0;
        while (line[start][i])
        {
            if (line[start][i] == 'N' || line[start][i] == 'S' ||
                line[start][i] == 'W' || line[start][i] == 'E')
            {
                character++;
            }
            if (line[start][i] != '0' && line[start][i] != '1' && 
                line[start][i] != ' ' && line[start][i] != '\t' &&
                line[start][i] != 'N' && line[start][i] != 'S' &&
                line[start][i] != 'W' && line[start][i] != 'E')
            {
                printf("error: unexpected chracter f line %d", start + 1); /**/
                exit(1);
            }
            i++;
        }
        start++;
    }
    if (character > 1)
    {
        printf("More than one character on the map.\n"); /**/
        exit(1);
    }
    else if (character == 0)
    {
        printf("There is no character in the map.\n"); /**/
        exit(1);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    t_map_info *map_data;
    map_data = malloc(sizeof(t_map_info));
    map_data->c_values = (int *)malloc(sizeof(int) * 3);
    map_data->f_values = (int *)malloc(sizeof(int) * 3);
    check_file_existence_and_extension(av[1]);
    read_and_store_map(av[1], map_data);
    init_map_line_ranges(map_data);
    //textures_parse(map_data);
    //map_parse(map_data);
    //show_info(map_data);
    //show_info(map_data);
    
    //has_gap_between_lines(map_data->map_content, map_data->map_start_index, map_data->map_end_index);
    check_gaps(map_data, 0, map_data->texture_start_index);
    check_0_to_end_texture(map_data->map_content, map_data->texture_start_index, map_data->map_start_index);
    check_gaps(map_data, map_data->texture_end_index + 1, map_data->map_start_index);
    check_gaps(map_data, map_data->map_end_index + 1, map_data->eof_index + 1);
    // had function dyal has gap chno kadir nsit hhhhh
    has_gap_between_lines(map_data->map_content, map_data->map_start_index, map_data->map_end_index);
    textures_parse(map_data);
    map_parse(map_data);
    //show_info(map_data);
    printf(" => parsing success <=");
    return (0);
}

// if char == 0 and char+1 == \0 or \n
// if char[0] == 0   or while (str[i++]) if (char == '0') return(1)

//no spaces f map in the left side 
//7ta nchecker map kamla 3ad nbda nchof wach kayn character tma wla la
// func to check the left edges, if == ' '||'\t', then printf("extra spaces in line %d") exit(1) [textures]
// ft_puterror: edit on error messages 
// display the all errors in stdout before exit(1).
// PARSE MAP CHARACTERS, PLAYER
// if we do a space in  map (in left edge)
// handle setting double textures

// case 1: check if the map is whole blank and have no content.
// case 2: check if there is no map part2 or no texture.
