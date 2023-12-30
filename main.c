#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"


/* ft split start */
static int	count_strings(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

int	ft_strlen_sep(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != c))
		i++;
	return (i);
}

char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**strings;
	int		i;
	int		total_strs;

	i = 0;
	total_strs = count_strings((char *)s, c);
	strings = (char **)malloc(sizeof(char *) * total_strs + 1);
	if (!strings)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			strings[i] = ft_word((char *)s, c);
			i++;
		}
		while (*s && !(*s == c))
			s++;
	}
	strings[i] = 0;
	return (strings);
}
/* ft_split end */

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	if (dst == src || !n)
		return (dst);
	index = 0;
	while (index < n)
	{
		*((char *) dst + index) = *((char *)src + index);
		index++;
	}
	return (dst);
}

int ft_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }
    // Check for the case where one string is shorter than the other
    return (*s1 - *s2);
}

char	*ft_strndup(char *s1, int n)
{
	char	*p;
	int		i;

	i = 0;
	p = calloc(ft_strlen(s1), sizeof(char));
	while (i < n)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
/*
texture/npn0.xpm\n  17
n = 15

texture/npn0.xpm
*/

// char    *fill_map(int map_fd, char *map_content, int index) {
//     char *line;
//     int i = 0;
//     while ((line = get_next_line(map_fd)) != NULL && i < index)
//         i++;
//     map_content = malloc(sizeof(char *) * ft_strlen(line));
//     return (ft_strdup(line));
// }

int	calc_lines(int map_fd)
{
	int	i;

	i = 0;
	while (get_next_line(map_fd) != NULL)
		i++;
	close(map_fd);
	return (i);
}

void is_valid(char *str) {
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

void get_file_extension(char *str) {
    int i = 0;
    while (str[i])
    {
        //printf("%d: %d\n", i, str[i]);
        i++;
    }
    int index_to_start = i - 4;
    //printf("mapfile start at ==> %s\n", str + index_to_start);
    if (ft_strcmp(str + index_to_start, ".cub") == 0) {
        is_valid(str);
    }
    else {
        write(2, "wrong file extention\n", 21);
        exit (1);
    }
}

void    check_num_of_texture(char **map) {
    int i = 0;
    int total_textures = 0;
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ') {
            total_textures++;
        }
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ') {
            total_textures++;
        }
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ') {
            total_textures++;
        }
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ') {
            total_textures++;
        }
        //
        else if (map[i][0] == 'C' && map[i][1] == ' ')
        {
            total_textures++;
        }
        else if (map[i][0] == 'F' && map[i][1] == ' ')
        {
            total_textures++;
        }
        i++;
    }
    if (total_textures != 6)
    {
        write(2, "invalid number of textures.\n", 28);
        exit(1);
    }
}

typedef struct s_map_info
{
    int     color_c;
    int     color_f;

    int     start_index;
    int     end_index;
    int     num_of_lines;
    int     len_of_line;

    char    **map_data;
    char    *ceiling;
    char    *floor;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
}   t_map_info;

void    check_texture_valid(char *texture)
{
    if (access(texture, F_OK) != 0)
    {
        printf("File not found.\n"); // write error
        exit(1);
    }
    return ;
}

void    check_xpm_extension(char *texture)
{
    int i = 0;
    while (texture[i])
        i++;
    int index_to_start = i - 4;
    if (ft_strcmp(texture + index_to_start, ".xpm") == 0)
    {
        //is_valid(texture)
    }
    else {
        write(2, "wrong texture extension.\n", 26);
        exit(1);
    }
}

void    check_textures(char *texture)
{
    check_xpm_extension(texture);
    check_texture_valid(texture);
}

void remove_trailing_newline(char *str) {
    int len = ft_strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        // Replace newline with null terminator:
        str[len - 1] = '\0';
    }
}

void    set_textures_values(char **map, t_map_info *map_data) {
    int i = 0;
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->no_texture = texture_split[1];
            remove_trailing_newline(map_data->no_texture);
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->no_texture);
            // if not xpm and if not valid
        }
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->so_texture = texture_split[1];
            remove_trailing_newline(map_data->so_texture);
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->so_texture);
        }
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->we_texture = texture_split[1];
            remove_trailing_newline(map_data->we_texture);
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->we_texture);
        }
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ea_texture = texture_split[1];
            remove_trailing_newline(map_data->ea_texture);
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->ea_texture);
        }
        // check c and f
        else if (map[i][0] == 'C' && map[i][1] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ceiling = texture_split[1];
            remove_trailing_newline(map_data->ceiling);
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
        }
        else if (map[i][0] == 'F' && map[i][1] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->floor = texture_split[1];
            remove_trailing_newline(map_data->floor);
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
        }
        i++;
    }
}

/***********    *************    *************   *************/

            /*    M A P     P A R S I N G     */

/***********    *************    *************   *************/

void    is_surrounded_by_Walls(char **map_content, t_map_info *map_data)
{
    int i = map_data->start_index;
    //int j;
    while (map_content[i])
    {
        if (i == map_data->start_index)
        {
            int j = 0;
            while (map_content[i][j]) {
                if (map_content[i][j] != '1')
                {
                    write(1, "**** check walls ****\n", 23);
                    exit(1);
                }
                j++;
            }
        }
        else if (i > map_data->start_index && i < map_data->end_index)
        {
            //printf("=========> %c, %d\n", map_content[i][38], map_data->len_of_line - 1);
            //printf("len of line is %d", map_data->len_of_line);
            if (map_content[i][0] != '1' || map_content[i][ft_strlen(map_content[i]) - 1] != '1')
            {
                write(2, "********\n", 9);
                exit(1);
            }
        }
        else if (i == map_data->end_index)
        {
            int j = 0;
            while (map_content[i][j]) {
                if (map_content[i][j] != '1')
                {
                    write(1, "**** check walls ****\n", 23);
                    exit(1);
                }
                j++;
            }
        }
        //printf("i = %d\n", i);
        i++;
    }
}


int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    t_map_info *map_data;
    get_file_extension(av[1]);
    int map = open(av[1], O_RDONLY);
    int map_total_lines = calc_lines(map);
    close(map);
    char **map_content = (char **)malloc(sizeof(char *) * (map_total_lines + 1));
    int i = 0;
    char *line;
    map = open(av[1], O_RDONLY);
    while ((line = get_next_line(map)) != NULL)
    {
        map_content[i] = malloc(sizeof(char *) * ft_strlen(line) + 1);
        map_content[i] = ft_strdup(line);
        i++;
    }
    close(map);
    /*  map */
    map_data = malloc(sizeof(t_map_info));
    map_data->len_of_line = 0;
    check_num_of_texture(map_content);
    set_textures_values(map_content, map_data);
    /* parse map 2 */
    //while loop until read the first 1
    // return first line 1, start map index
    i = 0;
    int flag = 0;
    while (map_content[i])
    {
        if (map_content[i][0] == '1')
        {
            if (flag == 0)
            {
                flag = 1;
                map_data->start_index = i;
                remove_trailing_newline(map_content[i]); // **
                map_data->len_of_line = ft_strlen(map_content[i]);
            }
            else if (flag == 1)
            {
                map_data->end_index = i;
                remove_trailing_newline(map_content[i]); // ** 
                // if (map_data->len_of_line != (int)ft_strlen(map_content[i])) {
                //     write(2, "--------\n", 9);
                //     exit(1);
                // }
            }
        }
        else if (map_content[i][0] != '1' && flag == 1)
        {
            write(2, "--------\n", 9);
            exit(1);
        }
        i++;
    }
    //printf("start index is: %d |\t%s", map_data->start_index, map_content[map_data->start_index]);
    //printf("end index is: %d |\t%s", map_data->end_index, map_content[map_data->end_index]);        
    
    // check walls 11111 both start & end line
    // check surounded wall each line 00 and 0[len] == 1
    is_surrounded_by_Walls(map_content, map_data);
    // check player != 1 then print error and exit

    // also check if there is another character instead of 0,1, and W S N E 
    printf("success\n");
    return 0;
}

// make
// ./parsing toowan.cub


