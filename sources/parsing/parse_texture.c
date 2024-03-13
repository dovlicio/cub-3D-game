/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:23:37 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/04 15:11:37 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	**ft_set_ptr(t_parse *parse, int i)
{
	if (i == 1)
		return ((void **)(&(parse->north_path)));
	else if (i == 2)
		return ((void **)(&(parse->west_path)));
	else if (i == 3)
		return ((void **)(&(parse->east_path)));
	else if (i == 4)
		return ((void **)(&(parse->south_path)));
	else if (i == 5)
		return ((void **)(&(parse->ceiling_color)));
	return ((void **)(&(parse->floor_color)));
}

static void	ft_increase_j(char *str, int *j)
{
	while (str[*j] && !ft_strchr(" \n", str[*j]))
		(*j)++;
}

void	ft_handle_textures(t_parse *parse, char *str, int *i, int t)
{
	int		j;
	int		start;
	char	**ptr;

	ptr = (char **)ft_set_ptr(parse, t);
	if (*ptr)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	j = 0;
	while (str[j] != ' ')
		j++;
	while (str[j] && str[j] == ' ')
		j++;
	if (str[j] && str[j] != '\n')
	{
		start = j;
		ft_increase_j(str, &j);
		*ptr = ft_substr(str, start, j - start);
		while (str[j] && str[j] == ' ')
			j++;
		if (str[j] && str[j] != '\n')
			ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	}
	if (!(*ptr))
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	*i += j;
}
