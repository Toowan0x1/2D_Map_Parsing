#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"

typedef struct s_map_info
{
    int     texture_start_index;
    int     texture_end_index;
    int     map_start_index;
    int     map_end_index;
    int     eof_index;
    int     num_of_lines;
    int     len_of_line;

    char    **map_content;
    char    *ceiling;
    char    *floor;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;

    int     color_c;
    int     color_f;
}   t_map_info;

/* helpers and utils */
void remove_trailing_newline(char *str) {
    int len = ft_strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        // Replace newline with null terminator:
        str[len - 1] = '\0';
        // if str[len] exist then free str[len] character.
    }
}

void    show_info(t_map_info *map_data)
{
    printf("\n");
    int index = map_data->texture_start_index;
    while (index <= map_data->map_end_index)
    {
        printf("i=%d=%s\n", index, map_data->map_content[index]);
        index++;
    }
    // printf("\n");
    // printf("textures start at index: %d\n", map_data->texture_start_index);
    // printf("textures end at index: %d\n", map_data->texture_end_index);
    // printf("map start at index: %d\n", map_data->map_start_index);
    // printf("map end at index: %d\n", map_data->map_end_index);
    // printf("map eof index: %d\n", map_data->eof_index);
    printf("\n ==> parsing successful <==\n");
}




/***********    *************    *************   *************/

            /*    M A P     P A R S I N G     */

/***********    *************    *************   *************/

void    check_unsurrounded_zeros(char **line, int i)
{
    int j;

    j = 0;
    while (line[i][j])
    {
        if (line[i][j] == ' ')
        {
            if (line[i - 1][j] == '0' || line[i + 1][j] == '0')
            {
                printf("MAP ERROR: Unsurrounded 0 detected in line %d\n", i + 1);
                exit(1);
            }
        }
        else if (line[i][j] == '0')
        {
            if ((line[i - 1][j] == ' ' || line[i + 1][j] == ' ') ||
                (j > (int)ft_strlen(line[i - 1]) - 1 || j > (int)ft_strlen(line[i + 1]) - 1))
            {
                printf("MAP ERROR: Unsurrounded 0 detected in line %d\n", i + 1);
                exit(1);
            }
        }
        j++;
    }
}

void    check_surrounded_by_ones(char *line)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ')
        {
            printf("MAP ERROR: The first or last line is not fully enclosed by walls.\n");
            exit(1);
        }
        i++;
    }
}

void    map_parse(t_map_info *map_data)
{
    int i;

    i = map_data->map_start_index;
    while (map_data->map_content[i] && i <= map_data->map_end_index)
    {
        if (i == map_data->map_start_index)
            check_surrounded_by_ones(map_data->map_content[map_data->map_start_index]);
        else if (i > map_data->map_start_index && i < map_data->map_end_index)
            check_unsurrounded_zeros(map_data->map_content, i);
        else if (i == map_data->map_end_index)
            check_surrounded_by_ones(map_data->map_content[map_data->map_end_index]);
        i++;
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

void    set_textures_values(char **map, t_map_info *map_data) {
    int i = 0;
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->no_texture = texture_split[1];
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
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
        }
        else if (map[i][0] == 'F' && map[i][1] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->floor = texture_split[1];
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

/*             T E X T U R E     P A R S I N G               */

/***********    *************    *************   *************/

void    check_number_of_texture(char **map) {
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

void    is_valid_color_range(char *str, t_map_info *map_data)
{
    int i = 0;
    int res = 0;
    (void)map_data;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
        {
            write(2, "*** invalid texture number ***\n", 31);
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
        else
        {
            write(2, "*** invalid texture number ***\n", 31);
            exit(1);
        }
        i++;
    }
    if (res > 255)
    {
        write(2, "*** texture number greather than 255 ***\n", 41);
        exit(1);
    }
}

void    is_valid_ceilling(t_map_info *map_data) {
    int c_commas = 0;
    int c_flag = 0;
    int i = 0;
    while (map_data->ceiling[i])
    {
        if ((map_data->ceiling[i] >= '0' && map_data->ceiling[i] <= '9') ||
            (map_data->ceiling[i] == '+' || map_data->ceiling[i] == '-'))
        {
            if (c_flag == 0)
            {
                is_valid_color_range(&map_data->ceiling[i], map_data);
                c_flag = 1;
            }
        }
        else if (map_data->ceiling[i] == ',')
        {
            c_commas++;
            if (c_flag == 1)
                c_flag = 0;
        }
        else
        {
            write(2, "*** texture error ***\n", 22);
            exit(1);
        }
        i++;
    }
}

void    is_valid_floor(t_map_info *map_data) {
    int f_commas = 0;
    int f_flag = 0;
    int i = 0;
    while (map_data->floor[i])
    {
        if ((map_data->floor[i] >= '0' && map_data->floor[i] <= '9') ||
            (map_data->floor[i] == '+' || map_data->floor[i] == '-'))
        {
            if (f_flag == 0)
            {
                is_valid_color_range(&map_data->floor[i], map_data);
                f_flag = 1;
            }
        }
        else if (map_data->floor[i] == ',')
        {
            f_commas++;
            if (f_flag == 1)
                f_flag = 0;
        }
        else
        {
            write(2, "*** texture error ***\n", 22);
            exit(1);
        }
        i++;
    }
}



int kmala(char *line) {
    int j = 0;
    if (!line[j])
        return (0);
    while (line[j]) {
        if (line[j] != '1' && line[j] != '0' && line[j] != ' ' && line[j] != '\t') {
            return 0; // Non-valid character found
        }
        j++;
    }

    return 1; // Valid line
}

//int get_map_first_line(char **lines)
//int get_map_first_line(t_map_info *map_data)
void get_map_first_line(t_map_info *map_data)
{
    int i;
    
    i = 0;
    while (map_data->map_content[i]) {
        if (kmala(map_data->map_content[i]))
        {
            map_data->map_start_index = i; // Found the first valid line, return its index
            return ;
        }
        i++;
    }
}

void    get_map_last_line(t_map_info *map_data)
{
    int i = map_data->map_start_index;
    while (map_data->map_content[i])
    {
        if (!map_data->map_content[i])
            break ;
        if (map_data->map_content[i][0] == '1' && map_data->map_content[i][ft_strlen(map_data->map_content[i]) - 1] == '1')
            map_data->map_end_index = i;
        else if (map_data->map_content[i][0] == '1' && !map_data->map_content[i][1])
            map_data->map_end_index = i;
        //if (kmala2(line[i]))
            //map_data->end_index = i;
        //else
            //map_data->end_index = i - 1;
        i++;
    }
}
// last line and gap between lines  .....

// n7seb gap mn map_end tal EOF of file

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
    close(map_fd);
    map_data->map_content = (char **)malloc(sizeof(char *) * (calc_lines(map_fd) + 1));
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



/***********    *************    *************   *************/

/*         S E T    M A P   L I N E   R A N G E S            */

/***********    *************    *************   *************/

void    get_eof_index(t_map_info *map_data)
{
    int i;

    i = 0;
    while (map_data->map_content[i])
        map_data->eof_index = i++;
}

void    get_texture_first_line(t_map_info *map_data)
{
    int i;
    int total_textures;

    i = 0;
    total_textures = 0;
    while (map_data->map_content[i])
    {
        if (map_data->map_content[i][0] == 'N' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'S' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'W' && map_data->map_content[i][1] == 'E' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'E' && map_data->map_content[i][1] == 'A' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'C' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'F' && map_data->map_content[i][2] == ' ')
            total_textures++;
        if (total_textures > 0)
        {
            map_data->texture_start_index = i;
            break ;
        }
        i++;
    }
}

void    get_texture_last_line(t_map_info *map_data)
{
    int i;
    int total_textures;

    i = 0;
    total_textures = 0;
    while (map_data->map_content[i])
    {
        if (map_data->map_content[i][0] == 'N' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'S' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'W' && map_data->map_content[i][1] == 'E' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'E' && map_data->map_content[i][1] == 'A' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'C' && map_data->map_content[i][1] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'F' && map_data->map_content[i][1] == ' ')
            total_textures++;
        i++;
        if (total_textures == 6)
        {
            map_data->texture_end_index = i;
            break ;
        }
    }
}

void    init_map_line_ranges(t_map_info *map_data)
{
    get_texture_first_line(map_data);
    get_texture_last_line(map_data);
    get_map_first_line(map_data);
    get_map_last_line(map_data);
    get_eof_index(map_data);
}

void    textures_parse(t_map_info *map_data)
{
    check_number_of_texture(map_data->map_content);
    set_textures_values(map_data->map_content, map_data); // values of direction
    is_valid_ceilling(map_data);
    is_valid_floor(map_data);
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
    textures_parse(map_data);
    has_gap_between_lines(map_data->map_content, map_data->map_start_index, map_data->map_end_index);
    map_parse(map_data);
    show_info(map_data);
    printf("****   success  ****");
    return (0);
}

/* bfff leak issue:
    e1r3p1% ./parsing map.cub
    zsh: segmentation fault  ./parsing map.cub
*/

// check jnab
// 7seb gap between texture and map before looping on map

// PARSE MAP CHARACTERS, PLAYER

/*
int color_c;
int color_f;
*/

/* checklist: */
// check player != 1 then print error and exit
// also check if there is another character instead of 0,1, and W S N E 
// check walls each line il fih another character
// check latest and first index of each line if its 1

// if valid color format
// has two comas
// is valid color range 
// valid floor and ceilling

// verify map edges

/*
texture/npn0.xpm\n  17
n = 15

texture/npn0.xpm
*/

/*
check double
check there is one player
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