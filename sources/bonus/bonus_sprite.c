/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:21:30 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/13 15:59:49 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

unsigned int	ft_get_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_draw_crossair(t_cub *cub)
{
	int	sh;
	int	sw;
	int	x;
	int	y;

	sh = SCREEN_HEIGHT / 2;
	sw = SCREEN_WIDTH / 2;
	while (sw >= SCREEN_WIDTH / 2 - 1)
	{
		x = SCREEN_WIDTH / 2 - 17;
		while (x < SCREEN_WIDTH / 2 - 4)
			cub->buffer[sh][x++] = (uint32_t)0x00FF80;
		x = SCREEN_WIDTH / 2 + 4;
		while (x < SCREEN_WIDTH / 2 + 17)
			cub->buffer[sh][x++] = (uint32_t)0x00FF80;
		y = SCREEN_HEIGHT / 2 - 17;
		while (y < SCREEN_HEIGHT / 2 - 4)
			cub->buffer[y++][sw] = (uint32_t)0x00FF80;
		y = SCREEN_HEIGHT / 2 + 4;
		while (y < SCREEN_HEIGHT / 2 + 17)
			cub->buffer[y++][sw] = (uint32_t)0x00FF80;
		sh--;
		sw--;
	}
}

void	ft_draw_gun(t_cub *cub, int t)
{
	int			y;
	int			x;
	int			x1;
	int			y1;
	uint32_t	color;

	y = 0;
	y1 = 340;
	while (y < 360)
	{
		x = 0;
		x1 = 450;
		while (x < 640)
		{
			color = ft_get_color(&cub->texture[t], x, y);
			if (color != 4278190080)
				cub->buffer[y1][x1] = color;
			x++;
			x1++;
		}
		y++;
		y1++;
	}
}

void	ft_copy_buffer(uint32_t (*buffer1)[1400], uint32_t (*buffer2)[1400])
{
	int	x;
	int	y;

	y = 0;
	while (y < 700)
	{
		x = 0;
		while (x < 1400)
		{
			buffer2[y][x] = buffer1[y][x];
			x++;
		}
		y++;
	}
}

void	sprite(t_cub *cub)
{
	ft_draw_crossair(cub);
	ft_copy_buffer(cub->buffer, cub->buff_copy);
	ft_draw_gun(cub, 6);
	ft_draw_buffer(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
	if (cub->sprite == 1)
	{
		ft_copy_buffer(cub->buff_copy, cub->buffer);
		ft_draw_gun(cub, 7);
		ft_draw_buffer(cub);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
		ft_copy_buffer(cub->buff_copy, cub->buffer);
		ft_draw_gun(cub, 8);
		ft_draw_buffer(cub);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
		cub->sprite = 0;
	}
}
