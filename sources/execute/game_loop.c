/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:21:53 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/13 17:54:48 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_for_wall(t_cub *cub)
{
	cub->hit = 0;
	while (cub->hit == 0)
	{
		if (cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}
		if (cub->parse->map[cub->map_y][cub->map_x] == '1')
			cub->hit = 1;
	}
	if (cub->side == 0)
		cub->perp_wall_dist = (cub->side_dist_x - cub->delta_dist_x);
	else
		cub->perp_wall_dist = (cub->side_dist_y - cub->delta_dist_y);
}

void	calc_step(t_cub *cub)
{
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->pos_x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->pos_x) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->pos_y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->pos_y) * cub->delta_dist_y;
	}
}

void	ray_cast(t_cub *cub)
{
	int	x;
	int	w;

	x = 0;
	w = SCREEN_WIDTH;
	while (x < w)
	{
		cub->camera_x = 2 * x / (double)w - 1;
		cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
		cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
		cub->map_x = (int)cub->pos_x;
		cub->map_y = (int)cub->pos_y;
		if (cub->ray_dir_x == 0)
			cub->delta_dist_x = 1e30;
		else
			cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
		if (cub->ray_dir_y == 0)
			cub->delta_dist_y = 1e30;
		else
			cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
		(calc_step(cub), check_for_wall(cub));
		(calc_start_n_end(cub), which_texture(cub));
		filling_buffer(cub, x);
		x++;
	}
}

int	game_loop(void	*ptr)
{
	t_cub	*cub;
	t_img	img;

	cub = (t_cub *)ptr;
	cub->img = &img;
	cub->img->img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub->img->img)
		fail_exit(cub, "Error\nCreation of image failed.\n");
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->size_line, &cub->img->endian);
	if (!cub->img->addr)
		(mlx_destroy_image(cub->mlx, cub->img->img), fail_exit(cub, "Error\n"));
	hook(cub);
	render_background(cub);
	ray_cast(cub);
	ft_draw_buffer(cub);
	clear_buffer(cub->buffer, SCREEN_HEIGHT, SCREEN_WIDTH);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img->img);
	return (0);
}
