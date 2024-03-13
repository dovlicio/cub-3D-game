/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:02:01 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/13 17:50:52 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_side(t_cub *cub)
{
	cub->dir_x = 0;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0;
	if (cub->parse->world_side == 'W')
	{
		cub->plane_y = -0.66;
		cub->dir_x = -1;
	}
	if (cub->parse->world_side == 'S')
	{
		cub->plane_x = -0.66;
		cub->dir_y = 1;
	}
	if (cub->parse->world_side == 'N')
	{
		cub->plane_x = 0.66;
		cub->dir_y = -1;
	}
	if (cub->parse->world_side == 'E')
	{
		cub->plane_y = 0.66;
		cub->dir_x = 1;
	}
}

void	init_player(t_cub *cub)
{
	cub->pos_x = cub->parse->pos_x + 0.5;
	cub->pos_y = cub->parse->pos_y + 0.5;
	init_player_side(cub);
}

void	init(t_cub *cub, t_parse *parse, t_img *texture, t_player *player)
{
	cub->player = player;
	cub->parse = parse;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_clean_parse(parse, "Error\nMlx initalization failed.\n");
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (!cub->win)
	{
		(mlx_destroy_display(cub->mlx), free(cub->mlx));
		ft_clean_parse(cub->parse,
			"Error\nWindow init initalization failed.\n");
	}
	cub->buffer = ft_calloc(SCREEN_HEIGHT * SCREEN_WIDTH, sizeof(uint32_t));
	if (!cub->buffer)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		ft_clean_parse(cub->parse, "Error\nMemory allocation failed.\n");
	}
	cub->texture = texture;
	init_player(cub);
	initialize_textures(cub);
}
