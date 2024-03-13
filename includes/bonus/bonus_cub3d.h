/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:46:22 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/13 17:41:12 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_CUB3D_H
# define BONUS_CUB3D_H

# include "mlx_int.h"
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <X11/Xlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/extensions/Xfixes.h>
# include <stdlib.h>
# include <stdint.h>
# include "../../libft/libft.h"
# include "bonus_error.h"
# include "bonus_parse.h"

# define SCREEN_WIDTH 1400
# define SCREEN_HEIGHT 700
# define TEXT_WIDTH 256
# define TEXT_HEIGHT 256
# define ROTATION_SPEED 0.15
# define MOVEMENT_SPEED 0.15

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

typedef struct s_back_gr
{
	float		ray_dir_x0;
	float		ray_dir_y0;
	float		ray_dir_x1;
	float		ray_dir_y1;
	int			p;
	float		pos_z;
	float		row_distance;
	float		floor_step_x;
	float		floor_step_y;
	float		floor_x;
	float		floor_y;
	int			cell_x;
	int			cell_y;
	int			tx;
	int			ty;
	int			tex_data_pos_floor;
	u_int32_t	color;
}			t_back_gr;

typedef struct s_cub
{
	char		prev;
	int			open;
	int			door;
	int			sprite;
	int			mm_i;
	int			mm_j;
	int			mm_x;
	int			mm_y;
	double		old_x;
	double		old_y;
	void		*mlx;
	void		*win;
	t_img		*img;
	t_parse		*parse;
	uint32_t	(*buffer)[SCREEN_WIDTH];
	uint32_t	(*buff_copy)[SCREEN_WIDTH];
	t_img		*texture;
	t_player	*player;
	t_back_gr	*backg;
	int			hide_mouse;
	int			mouse_trapped;
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
/*-------------BONUS/MINIMAP.C-------------*/
/*-------------------------------------------*/
void			ft_draw_minimap(t_cub *cub);
void			ft_draw_minimap_ram(t_cub *cub);
void			ft_draw_crossair(t_cub *cub);

/*-------------------------------------------*/
/*-------------EXECUTE/MLX_KEY.C-------------*/
/*-------------------------------------------*/
int				mlx_key(int keysum, void *cb);
int				release_key(int keysum, void *cb);

/*-------------------------------------------*/
/*----------EXECUTE/BONUS_ROTATE.C-----------*/
/*-------------------------------------------*/
void			hook(t_cub *cub);
void			r_rotating(t_cub *cub, double rotation);
void			l_rotating(t_cub *cub, double rotation);

/*-------------------------------------------*/
/*----------EXECUTE/INIT_TEXTURES.C----------*/
/*-------------------------------------------*/
void			initialize_textures(t_cub *cub);
void			clear_textures(t_cub *cub, t_img *texture);

/*-------------------------------------------*/
/*--------------EXECUTE/EXIT.C---------------*/
/*-------------------------------------------*/
void			clean_exit(t_cub *cub);
int				on_destroy(void *cb);
void			fail_exit(t_cub *cub, char *message);

/*-------------------------------------------*/
/*-----------EXECUTE/MLX_UTILS.C-------------*/
/*-------------------------------------------*/
void			my_mlx_pixel_put(t_img *data, int color, int x, int y);
int				create_rgb(int r, int g, int b);
void			clear_buffer(uint32_t (*buffer)[SCREEN_WIDTH], int h, int w);

/*-------------------------------------------*/
/*------------EXECUTE/RENDER.C---------------*/
/*-------------------------------------------*/
void			ft_draw_buffer(t_cub *cub);
void			render_background(t_cub *cub);

/*-------------------------------------------*/
/*--------EXECUTE/GAME_LOOP_UTILS.C----------*/
/*-------------------------------------------*/
int				game_loop(void	*ptr);
void			calc_start_n_end(t_cub *cub);
void			which_texture(t_cub *cub);
void			filling_buffer(t_cub *cub, int x);
int				mouse_rotation(int x, int y, t_cub *cub);

/*-------------------------------------------*/
/*----------EXECUTE/INIT.C------------*/
/*-------------------------------------------*/
void			init(t_cub *cub, t_parse *parse,
					t_img *texture, t_player *player);

/*-------------------------------------------*/
/*--EXECUTE/BONUS/BONUS_INIT_TEXTURES.C------*/
/*-------------------------------------------*/
void			initialize_textures_bonus(t_cub *cub);
void			destroy_textures(t_cub *cub, t_img *texture);

/*-------------------------------------------*/
/*------EXECUTE/BONUS/BONUS_RENDER.C---------*/
/*-------------------------------------------*/
void			render_background_bonus(t_cub *cub);

/*-------------------------------------------*/
/*-----------EXECUTE/MLX_UTILS.C-------------*/
/*-------------------------------------------*/
void			hide_mouse(t_cub *cub);
int				mouse_click(int button, int x, int y, t_cub *cub);

/*-------------------------------------------*/
/*-----------EXECUTE/BONUS_MOVING2.C---------*/
/*-------------------------------------------*/
void			reset_minimap(t_cub *cub, char temp);

/*-------------------------------------------*/
/*-----------EXECUTE/BONUS_SPRITE.C----------*/
/*-------------------------------------------*/
void			sprite(t_cub *cub);
unsigned int	ft_get_color(t_img *data, int x, int y);
void			ft_draw_crossair(t_cub *cub);

#endif
