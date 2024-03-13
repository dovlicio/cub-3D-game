/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:46:22 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/13 17:52:23 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <X11/Xlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdint.h>
# include "../libft/libft.h"
# include "error.h"
# include "parse.h"

# define SCREEN_WIDTH 1400
# define SCREEN_HEIGHT 700
# define TEXT_WIDTH 256
# define TEXT_HEIGHT 256
# define ROTATION_SPEED 0.09
# define MOVEMENT_SPEED 0.09

typedef struct s_img
{
	void		*img;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*addr;
	uint32_t	*texture;
}			t_img;

typedef struct s_player
{
	int	i_am_speed;
	int	sneaky_peaky;
	int	l_rotating;
	int	r_rotating;
	int	left;
	int	right;
	int	forward;
	int	backward;
	int	l;
	int	r;
	int	b;
	int	f;
}		t_player;

typedef struct s_mouse
{
	int					diff_x;
	float				rotation_speed;
	long long			time_elapsed;
	long long			current_time_usec;
}						t_mouse;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_parse		*parse;
	uint32_t	(*buffer)[SCREEN_WIDTH];
	t_img		*texture;
	t_player	*player;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		move_speed;
	double		rot_speed;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		old_dir_x;
	double		old_plane_x;
	int			tex_num;
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		step;
	double		tex_pos;
}				t_cub;

/*-------------------------------------------*/
/*-------------EXECUTE/MLX_KEY.C-------------*/
/*-------------------------------------------*/
int		mlx_key(int keysum, void *cb);
int		release_key(int keysum, void *cb);

/*-------------------------------------------*/
/*-------------EXECUTE/MOVING.C--------------*/
/*-------------------------------------------*/
void	hook(t_cub *cub);
void	r_rotating(t_cub *cub, double rotation);
void	l_rotating(t_cub *cub, double rotation);

/*-------------------------------------------*/
/*----------EXECUTE/INIT_TEXTURES.C----------*/
/*-------------------------------------------*/
void	initialize_textures(t_cub *cub);
void	clear_textures(t_cub *cub, t_img *texture);

/*-------------------------------------------*/
/*--------------EXECUTE/EXIT.C---------------*/
/*-------------------------------------------*/
void	clean_exit(t_cub *cub);
int		on_destroy(void *cb);
void	fail_exit(t_cub *cub, char *message);

/*-------------------------------------------*/
/*-----------EXECUTE/MLX_UTILS.C-------------*/
/*-------------------------------------------*/
void	my_mlx_pixel_put(t_img *data, int color, int x, int y);
int		create_rgb(int r, int g, int b);
void	clear_buffer(uint32_t (*buffer)[SCREEN_WIDTH], int h, int w);

/*-------------------------------------------*/
/*------------EXECUTE/RENDER.C---------------*/
/*-------------------------------------------*/
void	ft_draw_buffer(t_cub *cub);
void	render_background(t_cub *cub);

/*-------------------------------------------*/
/*--------EXECUTE/GAME_LOOP_UTILS.C----------*/
/*-------------------------------------------*/
int		game_loop(void	*ptr);
void	calc_start_n_end(t_cub *cub);
void	which_texture(t_cub *cub);
void	filling_buffer(t_cub *cub, int x);

/*-------------------------------------------*/
/*----------EXECUTE/INIT.C------------*/
/*-------------------------------------------*/
void	init(t_cub *cub, t_parse *parse, t_img *texture, t_player *player);

#endif
