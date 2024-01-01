/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 05:05:43 by oel-houm          #+#    #+#             */
/*   Updated: 2023/12/28 05:08:15 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"
#include <math.h>
#include <limits.h>

typedef struct s_map_size
{
	int		color_c;
	int		map_height;
	int		color_f;
	int		map_width;
	int		num_of_lines;
	int		len_of_line;
	int		number_horizontal;
	char	**map;
	char	**map_content;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}	t_map_size;

// typedef struct	s_map_size
// {
// 	char		**map_content;
// 	char		**map;
// 	int			num_of_lines;
// 	int			len_of_line;
// 	int			color_c;
// 	int			color_f;
// 	char		*no_texture;
// 	char		*so_texture;
// 	char		*ea_texture;
// 	char		*we_texture;
// }	t_map_size;

int		calc_lines(char *str);
void	get_cub_file_info(char *str, t_map_size *map_info);
int		parse_is_here_map(t_map_size *map_info);
void	check_content_order(t_map_size *map_info);
int		parsing(char *str, t_map_size *map_info);
void	test_parse_color(char *str);



/* check map cadre */

void	ft_puterror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i++], 1);
	}
	exit(1);
}

int	check_corners(t_map_size *map_info, int i, int j)
{
	if ((i > 0 && i < map_info->num_of_lines - 1))
	{
		if (j >= ft_strlen(map_info->map[i + 1])
			|| j >= ft_strlen(map_info->map[i - 1]))
			return (1);
	}
	if (map_info->map[i + 1][j] == ' ')
		return (1);
	if (map_info->map[i - 1][j] == ' ')
		return (1);
	if (!map_info->map[i][j + 1] || map_info->map[i][j + 1] == ' ')
		return (1);
	if (!map_info->map[i][j - 1] || map_info->map[i][j - 1] == ' ')
		return (1);
	return (0);
}

void	check_is_zero_surrounded(t_map_size *map_info)
{
	int	i;
	int	j;

	i = 1;
	while (map_info->map[i] && i < map_info->len_of_line - 1)
	{
		j = 1;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == '0')
			{
				if (check_corners(map_info, i, j))
					ft_puterror("0 is not surrounded\n");
			}
			j++;
		}
		i++;
	}
}

void	check_is_surrounded_by_wall(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j] && map[i][j] == ' ')
		j++;
	if (!map[i][j] || map[i][j] != '1')
		ft_puterror("invalid map\n");
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			ft_puterror("invalid map\n");
		j++;
	}
}

void	check_is_closed(char **map, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(map[i]);
	while (map[i][j] && map[i][j] != '1')
	{
		if (map[i][j] != ' ')
			ft_puterror("invalid map (not start by one)\n");
		j++;
	}
	while (map[i][len - 1] == ' ')
		len--;
	if (map[i][len - 1] != '1')
	{
		ft_puterror("invalid map (not end by one)\n");
	}
}

void	check_inside_map(t_map_size *map_info, int i)
{
	if (i > 0 && i < map_info->num_of_lines - 1)
		check_is_closed(map_info->map, i);
}

void	check_map_cadre(t_map_size *map_info)
{
	int	i;

	i = 1;
	check_is_surrounded_by_wall(map_info->map, 0);
	check_is_surrounded_by_wall(map_info->map, map_info->num_of_lines - 1);
	while (map_info->map[i])
	{
		check_inside_map(map_info, i);
		i++;
	}
	check_is_zero_surrounded(map_info);
}

/* helpers */

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	c1;

	c1 = (char)c;
	while (*s != '\0' && *s != c1)
		s++;
	if (*s == c1)
		return ((char *)s);
	else
		return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*d;

	i = 0;
	d = (char *)s;
	while (i < n)
	{
		*d++ = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;	

	tab = NULL;
	if (size && count > UINT_MAX / size)
		return (tab);
	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static int	word_count(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s != c && *s)
	{
		count ++;
		s++;
	}
	return (count);
}

static char	*tab_make(char *s, char c)
{
	int		wo_len;
	char	*tab;
	int		i;

	i = 0;
	wo_len = word_len(s, c);
	tab = malloc(sizeof(char) * (wo_len + 1));
	if (!tab)
		return (NULL);
	while (s[i] && i < wo_len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		ins_word;
	char	**result;

	ins_word = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			result[ins_word] = tab_make((char *)s, c);
			ins_word++;
		}
		while (*s && *s != c)
			s++;
	}
	result[ins_word] = 0;
	return (result);
}

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

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s1) + 1;
	p = (char *)malloc(len);
	if (!p || !s1)
		return (NULL);
	ft_memcpy(p, s1, len);
	return (p);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while ((s1[a] || s2[a]) && a < n)
	{
		if (s1[a] == s2[a])
			a++;
		else
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
	}
	return (0);
}



/********************/

// parse args:

static int	ft_strcmpp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

/* check if file exists */
int	is_valid(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		write(2, "file not found\n", 15);
		return (0);
	}
	close(fd);
	return (1);
}

/* get file extension .cub */
int	get_file_extension(char *str)
{
	int	i;
	int	index_to_start;

	i = 0;
	while (str[i])
		i++;
	index_to_start = i - 4;
	if (ft_strcmpp(str + index_to_start, ".cub"))
	{
		if (is_valid(str))
			return (0);
	}
	else
		write(2, "wrong file extension\n", 22);
	return (1);
}

// parse map

/* get map */

int	get_num_of_lines(char **content)
{
	int	i;
	int	j;

	i = 0;
	while (content[i] && content[i][0] != ' '
		&& content[i][0] != '1' && content[i][0] != '0')
		i++;
	j = i;
	while (content[i] && (content[i][0] == ' '
		|| content[i][0] == '1' || content[i][0] == '0'))
		i++;
	return (i - j);
}

void	allocate_spaces(t_map_size *map_info)
{
	int	i;

	i = 0;
	while (map_info->map_content[i])
	{
		if (map_info->map_content[i][0] == ' '
			|| map_info->map_content[i][0] == '0'
			|| map_info->map_content[i][0] == '1')
		{
			if (map_info->len_of_line < ft_strlen(map_info->map_content[i]))
				map_info->len_of_line = ft_strlen(map_info->map_content[i]);
		}
		i++;
	}
	i = 0;
	while (i < map_info->num_of_lines)
	{
		map_info->map[i] = calloc(map_info->len_of_line, 1);
		i++;
	}
}

void	fill_map(int count, t_map_size *map_info, int i, int j)
{
	if (count != map_info->num_of_lines - 1)
		map_info->map[j] = ft_strndup(map_info->map_content[i],
				ft_strlen(map_info->map_content[i]) - 2);
	else
		map_info->map[j] = ft_strdup(map_info->map_content[i]);
}

void	get_map(t_map_size *map_info)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	j = 0;
	map_info->len_of_line = 0;
	map_info->num_of_lines = get_num_of_lines(map_info->map_content);
	map_info->map = malloc(sizeof(char *) * (map_info->num_of_lines + 1));
	allocate_spaces(map_info);
	while (map_info->map_content[++i])
	{
		if (map_info->map_content[i][0] == ' '
			|| map_info->map_content[i][0] == '1'
			|| map_info->map_content[i][0] == '0')
		{
			fill_map(count, map_info, i, j);
			count++;
			j++;
		}
	}
	map_info->map[j] = NULL;
}

// check map

int	check_chars(char c)
{
	if (c != 'W' && c != 'S' && c != 'E' && c != 'N')
	{
		return (1);
	}
	return (0);
}

void	check_double(t_map_size *map_info)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (check_chars(map_info->map[i][j]) == 0)
				found++;
			j++;
		}
		i++;
	}
	if (found != 1)
	{
		write(2, "check their is one player\n", 27);
		exit (1);
	}
}

void	check_map(t_map_size *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] != ' ' && map_info->map[i][j] != '1'
				&& map_info->map[i][j] != '0'
				&& check_chars(map_info->map[i][j]))
			{
				write(2, "there is a wrong char in your map\n", 35);
				exit (1);
			}
			j++;
		}
		i++;
	}
	check_double(map_info);
	check_map_cadre(map_info);
}














int	parsing(char *str, t_map_size *map_info)
{
	if (get_file_extension(str))
		return (1);
	// get_cub_file_info(str, map_info);
	// check_content_order(map_info);
	// get_map_textures(map_info);
	// get_map(map_info);
	check_map(map_info);
	return (0);
}


int	main(int ac, char **av) {
	t_map_size	*map_info;
	map_info = malloc(sizeof(t_map_size) * 1);
	if (parsing(av[1], map_info))
		return("Shit", 1);
	return 0;
}













/*
void	check_is_closed(char **map, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(map[i]);
	while (map[i][j] && map[i][j] != '1')
	{
		if (map[i][j] != ' ')
			ft_puterror("invalid map (not start by one)\n");
		j++;
	}
	while (map[i][len - 1] == ' ')
		len--;
	if (map[i][len - 1] != '1')
	{
		ft_puterror("invalid map (not end by one)\n");
	}
}
*/

/*
int	check_wall(char **map, int i, int j)
{
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

*/



int	is_line_valid(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	{
		if (line[i] == '1')
			return (1);
		else if (line[i] == '0')
			return (0);
		i++;
	}
	return (0);
}