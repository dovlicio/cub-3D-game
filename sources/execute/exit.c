/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:59:21 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/13 17:52:55 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fail_exit(t_cub *cub, char *message)
{
	clear_textures(cub, cub->texture);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->buffer);
	ft_clean_parse(cub->parse, message);
}

int	on_destroy(void *cb)
{
	t_cub	*cub;

	cub = (t_cub *)cb;
	clear_textures(cub, cub->texture);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->buffer);
	clean_ft_clean_parse(cub->parse, "Exit.\n");
	return (0);
}

void	clean_exit(t_cub *cub)
{
	clear_textures(cub, cub->texture);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->buffer);
	clean_ft_clean_parse(cub->parse, "Exit.\n");
}
