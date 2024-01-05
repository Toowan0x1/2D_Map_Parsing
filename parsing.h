/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:34:00 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:34:37 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

typedef struct s_map_info
{
    int     texture_start_index;
    int     texture_end_index;
    int     map_start_index;
    int     map_end_index;
    int     eof_index;
    int     num_of_lines; //
    int     len_of_line; //

    char    **map_content;
    
    char    *ceiling; // _value
    char    *floor; //_value
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     *c_values;
    int     *f_values;
    int     c_color;
    int     f_color;

    /**/
    int     f_total;
    int     c_total;
    int     no_total;
    int     so_total;
    int     we_total;
    int     ea_total;
    /**/
}   t_map_info;

void    init_map_line_ranges(t_map_info *map_data);
void    map_parse(t_map_info *map_data);
void    textures_parse(t_map_info *map_data);
void    set_textures_values(char **map, t_map_info *map_data);

void    show_info(t_map_info *map_data);
void    remove_trailing_newline(char *str);
