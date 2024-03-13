/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_game_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdamnjan <vdamnjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:29:49 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/12 14:39:41 by vdamnjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	filling_buffer(t_cub *cub, int x)
{
	int			y;
	uint32_t	color;
	int			tex_data_pos;

	y = cub->draw_start;
	cub->step = 1.0 * TEXT_HEIGHT / cub->line_height;
	cub->tex_pos = (cub->draw_start - SCREEN_HEIGHT / 2
			+ cub->line_height / 2) * cub->step;
	while (y < cub->draw_end)
	{
		cub->tex_y = (int)cub->tex_pos & (TEXT_HEIGHT - 1);
		cub->tex_pos += cub->step;
		tex_data_pos = cub->tex_y * cub->texture[cub->tex_num].size_line
			+ cub->tex_x * 4;
		color = *(unsigned int *)(cub->texture[cub->tex_num].addr
				+ tex_data_pos);
		cub->buffer[y][x] = color;
		y++;
	}
}

void	calc_texx(t_cub *cub)
{
	if (cub->side == 0)
		cub->wall_x = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
	else
		cub->wall_x = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
	cub->wall_x -= floor(cub->wall_x);
	cub->tex_x = (int)(cub->wall_x * (double)TEXT_WIDTH);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		cub->tex_x = TEXT_WIDTH - cub->tex_x - 1;
	if (cub->side == 1 && cub->ray_dir_y < 0)
		cub->tex_x = TEXT_WIDTH - cub->tex_x - 1;
}

void	which_texture(t_cub *cub)
{
	if (cub->door == 1)
		cub->tex_num = 9;
	else if (cub->side == 1 && cub->ray_dir_y < 0)
		cub->tex_num = 2;
	else if (cub->side == 1 && cub->ray_dir_y > 0)
		cub->tex_num = 3;
	else if (cub->side == 0 && cub->ray_dir_x < 0)
		cub->tex_num = 0;
	else if (cub->side == 0 && cub->ray_dir_x > 0)
		cub->tex_num = 1;
	calc_texx(cub);
}

void	calc_start_n_end(t_cub *cub)
{
	if (cub->parse->map[cub->map_y][cub->map_x] == '2')
		cub->door = 1;
	cub->line_height = (int)(SCREEN_HEIGHT / cub->perp_wall_dist);
	cub->draw_start = -cub->line_height / 2 + SCREEN_HEIGHT / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + SCREEN_HEIGHT / 2;
	if (cub->draw_end >= SCREEN_HEIGHT)
		cub->draw_end = SCREEN_HEIGHT - 1;
}
