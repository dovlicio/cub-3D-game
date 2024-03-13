/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdamnjan <vdamnjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:55:34 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/05 12:47:10 by vdamnjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_check_tmp(t_parse *parse, int i)
{
	if (!ft_strchr("01 NWES\n", parse->tmp[i]))
	{
		free(parse->tmp);
		parse->tmp = NULL;
		return (0);
	}
	return (1);
}

int	ft_check_row(t_parse *parse, char *str)
{
	int	i;
	int	start;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (i < 1)
		return (0);
	parse->tmp = ft_substr(str, 0, i);
	if (!parse->tmp)
		ft_clean_parse(parse, MALLOC_FAILED_ERROR);
	i = 0;
	while (parse->tmp[i])
	{
		if (!ft_check_tmp(parse, i))
			return (0);
		i++;
	}
	start = 0;
	if (ft_strchr(parse->tmp, '1') || ft_strchr(parse->tmp, '0'))
		start = 1;
	free(parse->tmp);
	parse->tmp = NULL;
	return (start);
}

void	ft_copy_row(t_parse *parse, char *new, int i)
{
	int		j;

	j = 0;
	while (parse->copy[i][j])
	{
		new[j] = parse->copy[i][j];
		j++;
	}
	while (j < parse->map_w)
		new[j++] = ' ';
	new[j] = '\0';
}

void	ft_loop_data(t_parse *parse, char *str, int *i)
{
	if (!ft_strncmp(str, "NO ", 3))
		ft_handle_textures(parse, str, i, 1);
	else if (!ft_strncmp(str, "WE ", 3))
		ft_handle_textures(parse, str, i, 2);
	else if (!ft_strncmp(str, "EA ", 3))
		ft_handle_textures(parse, str, i, 3);
	else if (!ft_strncmp(str, "SO ", 3))
		ft_handle_textures(parse, str, i, 4);
	else if (!ft_strncmp(str, "C ", 2))
		ft_handle_colors(parse, str, i, 5);
	else if (!ft_strncmp(str, "F ", 2))
		ft_handle_colors(parse, str, i, 6);
	else
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
}
