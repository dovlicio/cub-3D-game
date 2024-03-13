/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:08:28 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/12 20:16:34 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	r_rotating(t_cub *cub, double rotation)
{
	if (cub->player->forward != 0 || cub->player->left != 0
		|| cub->player->backward != 0 || cub->player->right != 0)
		rotation /= 1.6;
	cub->old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(rotation) - cub->dir_y * sin(rotation);
	cub->dir_y = cub->old_dir_x * sin(rotation)
		+ cub->dir_y * cos(rotation);
	cub->old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(rotation)
		- cub->plane_y * sin(rotation);
	cub->plane_y = cub->old_plane_x * sin(rotation)
		+ cub->plane_y * cos(rotation);
}

void	l_rotating(t_cub *cub, double rotation)
{
	if (cub->player->forward != 0 || cub->player->left != 0
		|| cub->player->backward != 0 || cub->player->right != 0)
		rotation /= 1.6;
	cub->old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(-(rotation)) - cub->dir_y * sin(-(rotation));
	cub->dir_y = cub->old_dir_x * sin(-(rotation))
		+ cub->dir_y * cos(-(rotation));
	cub->old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(-(rotation))
		- cub->plane_y * sin(-(rotation));
	cub->plane_y = cub->old_plane_x * sin(-(rotation))
		+ cub->plane_y * cos(-(rotation));
}
