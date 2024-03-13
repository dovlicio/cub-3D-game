/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:56:40 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/13 16:00:10 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

static void	ft_mm_draw2(t_cub *cub, int i, int j, int t)
{
	int			x;
	int			y;
	uint32_t	color;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			color = ft_get_color(&cub->texture[t], x, y);
			cub->buffer[(i + 10) * 10 + y][(j + 10) * 10 + x] = color;
			x++;
		}
		y++;
	}
}

static void	ft_mm_draw(t_cub *cub, int i, int j, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			cub->buffer[(i + 10) * 10 + y][(j + 10) * 10 + x] = color;
			y++;
		}
		x++;
	}
}

void	ft_draw_minimap_ram(t_cub *cub)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	while (y < 210)
	{
		x = 0;
		while (x < 210)
		{
			color = ft_get_color(&cub->texture[10], x, y);
			if (color != 4278190080)
				cub->buffer[y][x] = color;
			x++;
		}
		y++;
	}
}

void	put_color_n_draw(t_cub *cub)
{
	if (cub->parse->map[cub->mm_y / 10][cub->mm_x / 10] == '1')
		ft_mm_draw2(cub, cub->mm_i, cub->mm_j, 14);
	else if (cub->parse->map[cub->mm_y / 10][cub->mm_x / 10] == '0')
		ft_mm_draw2(cub, cub->mm_i, cub->mm_j, 15);
	else if (cub->parse->map[cub->mm_y / 10][cub->mm_x / 10] == '2')
		ft_mm_draw2(cub, cub->mm_i, cub->mm_j, 13);
	else if (cub->parse->map[cub->mm_y / 10][cub->mm_x / 10] == '3')
		ft_mm_draw2(cub, cub->mm_i, cub->mm_j, 12);
	else
		ft_mm_draw2(cub, cub->mm_i, cub->mm_j, 11);
}

void	ft_draw_minimap(t_cub *cub)
{
	cub->mm_i = -10;
	while (cub->mm_i <= 10)
	{
		cub->mm_j = -10;
		while (cub->mm_j <= 10)
		{
			cub->mm_x = (int)(cub->pos_x + cub->mm_j) * 10;
			cub->mm_y = (int)(cub->pos_y + cub->mm_i) * 10;
			if (cub->mm_x >= 0 && cub->mm_x < cub->parse->map_w * 10 && \
				cub->mm_y >= 0 && cub->mm_y < cub->parse->map_h * 10)
				put_color_n_draw(cub);
			else
				ft_mm_draw(cub, cub->mm_i, cub->mm_j, (uint32_t)0x404040);
			cub->mm_j++;
		}
		cub->mm_i++;
	}
}
