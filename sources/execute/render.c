/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:19:00 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/07 22:54:06 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_background(t_cub *cub)
{
	int	xas;
	int	yas;
	int	*c;
	int	*f;

	c = cub->parse->ceiling_color;
	f = cub->parse->floor_color;
	yas = 0;
	while (yas < SCREEN_HEIGHT)
	{
		xas = 0;
		while (xas < SCREEN_WIDTH)
		{
			if (yas < SCREEN_HEIGHT / 2)
				cub->buffer[yas][xas] = create_rgb(c[0], c[1], c[2]);
			else
				cub->buffer[yas][xas] = create_rgb(f[0], f[1], f[2]);
			xas++;
		}
		yas++;
	}
}

void	ft_draw_buffer(t_cub *cub)
{
	int	y;
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(cub->img, cub->buffer[y][x], x, y);
			y++;
		}
		x++;
	}
}
