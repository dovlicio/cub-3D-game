/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:03:07 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/07 22:59:14 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	flood_fill(t_parse *parse, char **map, int y, int x)
{
	if (map[y][x] == '1' || y == 0 || y == parse->map_h - 1 || \
		x == 0 || x == parse->map_w - 1 || \
		map[y][x] == 'F' || map[y][x] == ' ')
	{
		if (map[y][x] == '1')
			return ;
		else if (y == 0 || y == parse->map_h - 1 || x == 0 || \
			x == parse->map_w - 1 || map[y][x] == ' ')
		{
			parse->error = 1;
		}
		return ;
	}
	else
	{
		map[y][x] = 'F';
		flood_fill(parse, map, y + 1, x);
		flood_fill(parse, map, y - 1, x);
		flood_fill(parse, map, y, x + 1);
		flood_fill(parse, map, y, x - 1);
	}
}
