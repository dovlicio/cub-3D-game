/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdamnjan <vdamnjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:46:16 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/13 15:30:29 by vdamnjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

int	main(int argc, char **argv)
{
	t_parse		parse;
	t_player	player;
	t_cub		cub;
	t_img		texture[16];

	ft_memset(&parse, 0, sizeof(parse));
	ft_parse_map(argc, argv[1], &parse);
	init(&cub, &parse, texture, &player);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, 17, (1L << 17), &on_destroy, &cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &mlx_key, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, &release_key, &cub);
	mlx_hook(cub.win, 6, 1L << 6, &mouse_rotation, &cub);
	mlx_hook(cub.win, ButtonPress, ButtonPressMask, &mouse_click, &cub);
	mlx_loop(cub.mlx);
}
