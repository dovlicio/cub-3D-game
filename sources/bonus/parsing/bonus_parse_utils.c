/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdamnjan <vdamnjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:33:29 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/12 16:42:02 by vdamnjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/bonus_cub3d.h"

void	ft_check_data(t_parse *parse)
{
	if (!parse->east_path)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	else if (!parse->west_path)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	else if (!parse->north_path)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	else if (!parse->south_path)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	else if (!parse->ceiling_path)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	else if (!parse->floor_path)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
}

void	ft_check_map(t_parse *parse, char *temp, int j)
{
	int	i;
	int	n;
	int	k;

	n = 0;
	i = j;
	while (temp[i])
	{
		if (!ft_strchr(" 0321NWES\n", temp[i]))
			ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
		if (ft_strchr("NWES", temp[i]))
			n++;
		if (temp[i] == '\n')
		{
			k = i + 1;
			while (temp[k] && !ft_strchr("1230\n", temp[k]))
				k++;
			if (!temp[k] || temp[k] == '\n')
				ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
		}
		i++;
	}
	if (n != 1)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
}

void	ft_get_player_position(t_parse *parse)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (parse->copy[y])
	{
		x = 0;
		while (parse->copy[y][x])
		{
			if (ft_strchr("EWSN", parse->copy[y][x]))
			{
				parse->world_side = parse->copy[y][x];
				parse->pos_y = y;
				parse->pos_x = x;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	ft_get_map_size(t_parse *parse)
{
	int	i;

	i = 0;
	parse->map_w = 0;
	while (parse->copy[i])
	{
		if (((int)ft_strlen(parse->copy[i])) > parse->map_w)
			parse->map_w = (int)(ft_strlen(parse->copy[i]));
		i++;
	}
	i = 0;
	while (parse->copy[i])
		i++;
	parse->map_h = i;
}
