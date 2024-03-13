/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:46:16 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/07 23:19:37 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_parse		parse;
	t_player	player;
	t_cub		cub;
	t_img		texture[4];

	ft_memset(&player, 0, sizeof(player));
	ft_memset(&parse, 0, sizeof(parse));
	ft_parse_map(argc, argv[1], &parse);
	init(&cub, &parse, texture, &player);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, 17, (1L << 17), &on_destroy, &cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &mlx_key, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, &release_key, &cub);
	mlx_loop(cub.mlx);
}
