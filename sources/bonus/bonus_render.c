/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:46:03 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/11 20:06:53 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	init_and_floor(t_cub *cub, int y)
{
	cub->backg->ray_dir_x0 = cub->dir_x - cub->plane_x;
	cub->backg->ray_dir_y0 = cub->dir_y - cub->plane_y;
	cub->backg->ray_dir_x1 = cub->dir_x + cub->plane_x;
	cub->backg->ray_dir_y1 = cub->dir_y + cub->plane_y;
	cub->backg->p = y - SCREEN_HEIGHT / 2;
	cub->backg->pos_z = 0.5 * SCREEN_HEIGHT;
	cub->backg->row_distance = cub->backg->pos_z / cub->backg->p;
	cub->backg->floor_step_x = cub->backg->row_distance
		* (cub->backg->ray_dir_x1 - cub->backg->ray_dir_x0) / SCREEN_WIDTH;
	cub->backg->floor_step_y = cub->backg->row_distance
		* (cub->backg->ray_dir_y1 - cub->backg->ray_dir_y0) / SCREEN_WIDTH;
	cub->backg->floor_x = cub->pos_x
		+ cub->backg->row_distance * cub->backg->ray_dir_x0;
	cub->backg->floor_y = cub->pos_y
		+ cub->backg->row_distance * cub->backg->ray_dir_y0;
}

void	cell_and_floor(t_cub *cub)
{
	cub->backg->cell_x = (int)(cub->backg->floor_x);
	cub->backg->cell_y = (int)(cub->backg->floor_y);
	cub->backg->tx = (int)(TEXT_WIDTH
			* (cub->backg->floor_x - cub->backg->cell_x)) & (TEXT_WIDTH - 1);
	cub->backg->ty = (int)(TEXT_HEIGHT
			* (cub->backg->floor_y - cub->backg->cell_y)) & (TEXT_HEIGHT - 1);
	cub->backg->floor_x += cub->backg->floor_step_x;
	cub->backg->floor_y += cub->backg->floor_step_y;
	cub->backg->tex_data_pos_floor = cub->backg->ty
		* cub->texture[4].size_line + cub->backg->tx * 4;
}

void	set_color(t_cub *cub, int x, int y)
{
	cub->backg->color = *(u_int32_t *)(cub->texture[4].addr
			+ cub->backg->tex_data_pos_floor);
	cub->backg->color = (cub->backg->color >> 1) & 8355711;
	cub->buffer[y][x] = cub->backg->color;
	cub->backg->tx = (int)(TEXT_WIDTH / 3 * (cub->backg->floor_x
				- cub->backg->cell_x)) & (TEXT_WIDTH - 1);
	cub->backg->ty = (int)(TEXT_HEIGHT / 3 * (cub->backg->floor_y
				- cub->backg->cell_y)) & (TEXT_HEIGHT - 1);
	cub->backg->tex_data_pos_floor = cub->backg->ty
		* cub->texture[5].size_line + cub->backg->tx * 4;
	cub->backg->color = *(u_int32_t *)(cub->texture[5].addr
			+ cub->backg->tex_data_pos_floor);
	cub->backg->color = (cub->backg->color >> 1) & 8355711;
	cub->buffer[SCREEN_HEIGHT - y - 1][x] = cub->backg->color;
}

void	render_background_bonus(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		init_and_floor(cub, y);
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			cell_and_floor(cub);
			set_color(cub, x, y);
			x++;
		}
		y++;
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
