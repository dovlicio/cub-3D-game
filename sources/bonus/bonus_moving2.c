/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_moving2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:43:25 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/12 20:02:10 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	reset_minimap(t_cub *cub, char temp)
{
	if (cub->parse->map[(int)cub->old_y][(int)cub->old_x] != \
	cub->parse->map[(int)cub->pos_y][(int)cub->pos_x])
	{
		temp = cub->parse->map[(int)cub->pos_y][(int)cub->pos_x];
		cub->parse->map[(int)cub->pos_y][(int)cub->pos_x] = \
			cub->parse->map[(int)cub->old_y][(int)cub->old_x];
		cub->parse->map[(int)cub->old_y][(int)cub->old_x] = cub->prev;
		cub->prev = temp;
	}
}

int	mouse_click(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (button == 1 && cub->mouse_trapped == 1)
		cub->sprite = 1;
	else if (button == 3 && cub->mouse_trapped == 1)
		cub->open = 1;
	return (0);
}

void	check_speed(t_mouse *mouse)
{
	if (mouse->rotation_speed >= 0.09 && abs(mouse->diff_x) < 150)
		mouse->rotation_speed = 0.075;
	else if (mouse->rotation_speed >= 0.09 && abs(mouse->diff_x) > 150)
		mouse->rotation_speed = 0.075;
}

float	calculate_rotation_speed(int diff_x, long long time_elapsed)
{
	float	distance;
	float	speed;

	if (time_elapsed == 0)
		return (0.0f);
	distance = abs(diff_x);
	speed = distance / time_elapsed;
	return (speed * ROTATION_SPEED);
}

int	mouse_rotation(int x, int y, t_cub *cub)
{
	static long long	prev_time = 0;
	static int			prev_x = SCREEN_WIDTH / 2;
	struct timeval		current_time;
	t_mouse				mouse;

	((void)y, gettimeofday(&current_time, NULL));
	mouse.current_time_usec = current_time.tv_sec
		* 1000000LL + current_time.tv_usec;
	mouse.time_elapsed = mouse.current_time_usec - prev_time;
	prev_time = mouse.current_time_usec;
	mouse.diff_x = x - prev_x;
	prev_x = x;
	if (cub->mouse_trapped == 1 && mouse.diff_x != 0)
	{
		mlx_mouse_move(cub->mlx, cub->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		mouse.rotation_speed = calculate_rotation_speed(mouse.diff_x,
				mouse.time_elapsed);
		check_speed(&mouse);
		if (x < (SCREEN_WIDTH / 2))
			l_rotating(cub, mouse.rotation_speed);
		else if (x > (SCREEN_WIDTH / 2))
			r_rotating(cub, mouse.rotation_speed);
		prev_x = x;
	}
	return (0);
}
