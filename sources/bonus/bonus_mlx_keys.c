/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdamnjan <vdamnjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:35:17 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/12 18:02:29 by vdamnjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	wasd_press_key(int keysum, t_cub *cub)
{
	cub->player->forward = 0;
	cub->player->backward = 0;
	cub->player->right = 0;
	cub->player->left = 0;
	if (keysum == 'a')
	{
		cub->player->left = 1;
		cub->player->l = 1;
	}
	else if (keysum == 'd')
	{
		cub->player->right = 1;
		cub->player->r = 1;
	}
	else if (keysum == 's')
	{
		cub->player->backward = 1;
		cub->player->b = 1;
	}
	else if (keysum == 'w')
	{
		cub->player->forward = 1;
		cub->player->f = 1;
	}
}

int	mlx_key(int keysum, void *cb)
{
	t_cub	*cub;

	cub = (t_cub *)cb;
	if (keysum == 65307)
		clean_exit(cub);
	else if (keysum == 65470)
		hide_mouse(cub);
	else if (keysum == 65505)
		cub->player->i_am_speed = 1;
	else if (keysum == 65507)
		cub->player->sneaky_peaky = 1;
	else if (keysum == 'a' || keysum == 'd' || keysum == 's' || keysum == 'w')
		wasd_press_key(keysum, cub);
	else if (keysum == 65361)
		cub->player->l_rotating = 1;
	else if (keysum == 65363)
		cub->player->r_rotating = 1;
	else if (keysum == ' ')
	{
		if (!cub->open)
			cub->open = 1;
	}
	return (0);
}

void	sw_release_key(int keysum, t_cub *cub)
{
	if (keysum == 's')
	{
		cub->player->backward = 0;
		cub->player->b = 0;
		if (cub->player->r == 1)
			cub->player->right = 1;
		if (cub->player->l == 1)
			cub->player->left = 1;
	}
	else if (keysum == 'w')
	{
		cub->player->f = 0;
		cub->player->forward = 0;
		if (cub->player->r == 1)
			cub->player->right = 1;
		if (cub->player->l == 1)
			cub->player->left = 1;
	}
}

void	ad_release_key(int keysum, t_cub *cub)
{
	if (keysum == 'a')
	{
		cub->player->l = 0;
		cub->player->left = 0;
		if (cub->player->f == 1)
			cub->player->forward = 1;
		if (cub->player->b == 1)
			cub->player->backward = 1;
	}
	else if (keysum == 'd')
	{
		cub->player->r = 0;
		cub->player->right = 0;
		if (cub->player->f == 1)
			cub->player->forward = 1;
		if (cub->player->b == 1)
			cub->player->backward = 1;
	}
}

int	release_key(int keysum, void *cb)
{
	t_cub	*cub;

	cub = (t_cub *)cb;
	if (keysum == 's' || keysum == 'w')
		sw_release_key(keysum, cub);
	else if (keysum == 65505)
		cub->player->i_am_speed = 0;
	else if (keysum == 65507)
		cub->player->sneaky_peaky = 0;
	else if (keysum == 65361)
		cub->player->l_rotating = 0;
	else if (keysum == 65363)
		cub->player->r_rotating = 0;
	else if (keysum == 'a' || keysum == 'd')
		ad_release_key(keysum, cub);
	else if (keysum == ' ')
		cub->open = 0;
	return (0);
}
