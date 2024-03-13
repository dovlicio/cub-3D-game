/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:09:33 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/11 20:07:02 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	clear_buffer(uint32_t (*buffer)[SCREEN_WIDTH], int h, int w)
{
	int	y;
	int	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
			buffer[y][x++] = 0;
		y++;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *data, int color, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	loop_mlx(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, &game_loop, &cub);
	mlx_hook(cub->win, 17, (1L << 17), &on_destroy, cub);
	mlx_hook(cub->win, KeyPress, KeyPressMask, &mlx_key, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, &release_key, cub);
	mlx_loop(cub->mlx);
}

void	hide_mouse(t_cub *cub)
{
	t_xvar		*var;
	t_win_list	*win;

	var = (t_xvar *)cub->mlx;
	win = (t_win_list *)cub->win;
	if (cub->hide_mouse == 0)
	{
		XFixesHideCursor(var->display, win->window);
		XGrabPointer(var->display, win->window, True, 0,
			GrabModeAsync, GrabModeAsync, win->window, None, CurrentTime);
		cub->hide_mouse = 1;
		cub->mouse_trapped = 1;
	}
	else if (cub->hide_mouse == 1)
	{
		XFixesShowCursor(var->display, win->window);
		XUngrabPointer(var->display, CurrentTime);
		cub->mouse_trapped = 0;
		cub->hide_mouse = 0;
	}
}
