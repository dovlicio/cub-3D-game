/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:38:19 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/12 20:01:42 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PARSE_H
# define BONUS_PARSE_H

typedef struct s_parse
{
	char	**map;
	char	**copy;
	char	*tmp;
	char	*map_path;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	char	*ceiling_path;
	char	*floor_path;
	int		pos_x;
	int		pos_y;
	int		map_w;
	int		map_h;
	char	world_side;
	int		error;
}			t_parse;

/*../parsing/parse_map.c*/
void	ft_parse_map(int argc, char *map_path, t_parse *parse);

/*../parsing/parse_map_utils.c*/
void	ft_copy_row(t_parse *parse, char *new, int i);
void	ft_loop_data(t_parse *parse, char *str, int *i);
int		ft_check_row(t_parse *parse, char *str);

/*../parsing/flood_fill.c*/
void	flood_fill(t_parse *parse, char **map, int y, int x);

/*../parsing/parse_colors.c*/
void	ft_handle_colors(t_parse *parse, char *str, int *i, int c);

/*../parsing/parse_colors_utils.c*/
void	ft_set_tmp(t_parse *parse, int start, int *j, char *str);

/*../parsing/parse_textures.c*/
void	ft_handle_textures(t_parse *parse, char *str, int *i, int t);
void	**ft_set_ptr(t_parse *parse, int i);

/*../parsing/cleaning.c*/
void	free_matrix(char **matrix);
void	ft_clean_parse(t_parse *parse, char *error);
void	free_new(t_parse *parse, int i, char *new);
void	clean_ft_clean_parse(t_parse *parse, char *error);

/*../parsing/error.c*/
int		err(char *error);
void	ft_check_argc(int argc);
void	ft_check_map_name(char *map_path);

/*../parsing/parse_utils.c*/
void	ft_check_data(t_parse *parse);
void	ft_check_map(t_parse *parse, char *temp, int j);
void	ft_get_player_position(t_parse *parse);
void	ft_get_map_size(t_parse *parse);

#endif
