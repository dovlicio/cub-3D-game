/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_moving.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:59:12 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/12 20:12:51 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	move_bw(t_cub *cub, double move)
{
	if (cub->parse->map[(int)(cub->pos_y)]
		[(int)(cub->pos_x - cub->dir_x * (move + 0.2))]
		!= '1' && cub->parse->map[(int)(cub->pos_y)]
		[(int)(cub->pos_x - cub->dir_x * (move + 0.2))] != '2')
		cub->pos_x -= cub->dir_x * move;
	if (cub->parse->map[(int)(cub->pos_y - cub->dir_y * (move + 0.2))]
		[(int)(cub->pos_x)] != '1' && cub->parse->map[(int)(cub->pos_y
		- cub->dir_y * (move + 0.2))]
		[(int)(cub->pos_x)] != '2')
		cub->pos_y -= cub->dir_y * move;
}

void	move_fw_or_bw(t_cub *cub, double move)
{
	if (cub->player->forward == 1)
	{
		if (cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x + cub->dir_x * (move + 0.2))]
			!= '1' && cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x + cub->dir_x * (move + 0.2))] != '2')
			cub->pos_x += cub->dir_x * move;
		if (cub->parse->map[(int)(cub->pos_y + cub->dir_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '1' && cub->parse->map[(int)(cub->pos_y
			+ cub->dir_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '2')
			cub->pos_y += cub->dir_y * move;
	}
	if (cub->player->backward == 1)
		move_bw(cub, move);
}

void	move_r(t_cub *cub, double move)
{
	if (cub->parse->map[(int)(cub->pos_y)]
		[(int)(cub->pos_x - cub->plane_x * (move + 0.2))]
		!= '1' && cub->parse->map[(int)(cub->pos_y)]
		[(int)(cub->pos_x - cub->plane_x * (move + 0.2))] != '2')
		cub->pos_x -= cub->plane_x * move;
	if (cub->parse->map[(int)(cub->pos_y - cub->plane_y * (move + 0.2))]
		[(int)(cub->pos_x)] != '1' && cub->parse->map[(int)(cub->pos_y
		- cub->plane_y * (move + 0.2))]
		[(int)(cub->pos_x)] != '2')
		cub->pos_y -= cub->plane_y * move;
}

void	move_l_or_r(t_cub *cub, double move)
{
	if (cub->player->right == 1)
	{
		if (cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x + cub->plane_x * (move + 0.2))]
			!= '1' && cub->parse->map[(int)(cub->pos_y)]
			[(int)(cub->pos_x + cub->plane_x * (move + 0.2))] != '2')
			cub->pos_x += cub->plane_x * move;
		if (cub->parse->map[(int)(cub->pos_y + cub->plane_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '1' && cub->parse->map[(int)(cub->pos_y
			+ cub->plane_y * (move + 0.2))]
			[(int)(cub->pos_x)] != '2')
			cub->pos_y += cub->plane_y * move;
	}
	if (cub->player->left == 1)
		move_r(cub, move);
}

void	hook(t_cub *cub)
{
	double	move;
	double	rotation;
	char	temp;

	temp = '\0';
	if (cub->player->i_am_speed == 1)
		move = MOVEMENT_SPEED * 1.5;
	else if (cub->player->sneaky_peaky == 1)
		move = MOVEMENT_SPEED / 1.5;
	else
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
	reset_minimap(cub, temp);
}
