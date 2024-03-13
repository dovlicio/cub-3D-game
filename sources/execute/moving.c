/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:59:12 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/07 21:12:31 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	r_rotating(t_cub *cub, double rotation)
{
	if (cub->player->r_rotating == 1)
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

void	move_fw_or_bw(t_cub *cub, double move)
{
	if (cub->player->forward == 1)
	{
		if (cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x + cub->dir_x * (move + 0.2))] != '1')
			cub->pos_x += cub->dir_x * move;
		if (cub->parse->map[(int)(cub->pos_y + cub->dir_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '1')
			cub->pos_y += cub->dir_y * move;
	}
	if (cub->player->backward == 1)
	{
		if (cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x - cub->dir_x * (move + 0.2))] != '1')
			cub->pos_x -= cub->dir_x * move;
		if (cub->parse->map[(int)(cub->pos_y - cub->dir_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '1')
			cub->pos_y -= cub->dir_y * move;
	}
}

void	move_l_or_r(t_cub *cub, double move)
{
	if (cub->player->right == 1)
	{
		if (cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x + cub->plane_x * (move + 0.2))] != '1')
			cub->pos_x += cub->plane_x * move;
		if (cub->parse->map[(int)(cub->pos_y + cub->plane_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '1')
			cub->pos_y += cub->plane_y * move;
	}
	if (cub->player->left == 1)
	{
		if (cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x - cub->plane_x * (move + 0.2))] != '1')
			cub->pos_x -= cub->plane_x * move;
		if (cub->parse->map[(int)(cub->pos_y - cub->plane_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '1')
			cub->pos_y -= cub->plane_y * move;
	}
}

void	hook(t_cub *cub)
{
	double	move;
	double	rotation;

	move = MOVEMENT_SPEED;
	rotation = ROTATION_SPEED;
	if (cub->player->r_rotating == 1)
		r_rotating(cub, rotation);
	if (cub->player->l_rotating == 1)
		l_rotating(cub, rotation);
	if (cub->player->right == 1 || cub->player->left == 1)
		move_l_or_r(cub, move);
	if (cub->player->forward == 1 || cub->player->backward)
		move_fw_or_bw(cub, move);
}
