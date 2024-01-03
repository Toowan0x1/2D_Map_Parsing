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

void    has_gap_between_lines(char **line, int start, int end)
{
    int i = 0;
    while (start <= end)
    {
        if (line[start] && line[start][0] == 0)
        {
            printf("%c\n", line[start][i]);
            printf("map gaps 1\n");
            exit(1);
        }
        i = 0;
        while (line[start][i])
        {
            if (line[start][i] != '0' && line[start][i] != '1' && line[start][i] != 'W' && line[start][i] != ' ' && line[start][i] != '\t')
            {
                printf("start is %d %s", start, line[start]);
                printf("%c\n", line[start][i]);
                printf("maps gaps character \n");
                exit(1);
            }
            i++;
        }
        start++;
    }
}

void is_file_valid(char *str) {
    int fd;

    fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        write(2, "file not found\n", 15);
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
        write(2, "wrong file extention\n", 21);
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
                printf("9wada f line %d\n", start+1);
                exit(1);
            }
            i++;
        }
        start++;
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
    textures_parse(map_data);
    has_gap_between_lines(map_data->map_content, map_data->map_start_index, map_data->map_end_index);
    map_parse(map_data);
    //show_info(map_data);
    
    check_gaps(map_data, 0, map_data->texture_start_index);
    //check mabin index 0 to tetxure_end
    check_gaps(map_data, map_data->texture_end_index, map_data->map_start_index);
    check_gaps(map_data, map_data->map_end_index + 1, map_data->eof_index + 1);
    
    printf(" => parsing sucess <=");
    return (0);
}

// if char == 0 and char+1 == \0 or \n
// if char[0] == 0   or while (str[i++]) if (char == '0') return(1)

// edit on error messages 

/* checklist: */
// PARSE MAP CHARACTERS, PLAYER
// check player != 1 then print error and exit
// also check if there is another character instead of 0,1, and W S N E 
// check walls each line il fih another character
/*
ft_put_error std2
int	check_chars(char c)
{
	if (c != 'W' && c != 'S' && c != 'E' && c != 'N')
	{
		return (1);
	}
	return (0);
}
*/

/*
texture/npn0.xpm\n  17
n = 15

texture/npn0.xpm
*/
