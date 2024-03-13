/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:34:08 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/13 18:03:19 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/bonus_cub3d.h"

void	destroy_textures(t_cub *cub, t_img *texture)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (texture[i].img)
			mlx_destroy_image(cub->mlx, texture[i].img);
		i++;
	}
}

void	check_textures_bonus(t_cub *cub, t_img *texture)
{
	if (!texture[0].img || !texture[1].img
		|| !texture[2].img || !texture[3].img
		|| !texture[4].img || !texture[5].img
		|| !texture[6].img || !texture[7].img
		|| !texture[8].img || !texture[9].img
		|| !texture[10].img || !texture[11].img
		|| !texture[12].img || !texture[13].img
		|| !texture[14].img || !texture[15].img)
	{
		destroy_textures(cub, texture);
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		free(cub->buff_copy);
		free(cub->buffer);
		ft_clean_parse(cub->parse, "Failed to initialize images.\n");
	}
	return ;
}

void	get_data_addr(t_cub *cub, t_img *texture)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		texture[i].addr = mlx_get_data_addr(texture[i].img, &texture[i]
				.bits_per_pixel, &texture[i].size_line, &texture[i].endian);
		if (!(texture[i].addr))
			fail_exit(cub, "Error\nFailed to get addr of image\n");
		i++;
	}
}

void	init_textures_minimap(t_cub *cub, t_img *texture)
{
	texture[9].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/scifi.xpm", &texture[9].width, &texture[9].height);
	texture[10].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/mmram.xpm", &texture[9].width, &texture[9].height);
	texture[11].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/igrac.xpm", &texture[11].width, &texture[11].height);
	texture[12].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/open.xpm", &texture[12].width, &texture[12].height);
	texture[13].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/close.xpm", &texture[13].width, &texture[13].height);
	texture[14].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/mmzid.xpm", &texture[14].width, &texture[14].height);
	texture[15].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/mmpod.xpm", &texture[15].width, &texture[15].height);
}

void	initialize_textures_bonus(t_cub *cub)
{
	t_img	*texture;

	texture = cub->texture;
	texture[0].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse->east_path, &texture[0].width, &texture[0].height);
	texture[1].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse->west_path, &texture[1].width, &texture[1].height);
	texture[2].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse->north_path, &texture[2].width, &texture[2].height);
	texture[3].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse->south_path, &texture[3].width, &texture[3].height);
	texture[4].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse->floor_path, &texture[4].width, &texture[4].height);
	texture[5].img = mlx_xpm_file_to_image(cub->mlx,
			cub->parse->ceiling_path, &texture[5].width, &texture[5].height);
	texture[6].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/shotgun1.xpm", &texture[6].width, &texture[6].height);
	texture[7].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/shotgun2.xpm", &texture[7].width, &texture[7].height);
	texture[8].img = mlx_xpm_file_to_image(cub->mlx,
			"textures/shotgun3.xpm", &texture[8].width, &texture[8].height);
	init_textures_minimap(cub, texture);
	check_textures_bonus(cub, cub->texture);
	get_data_addr(cub, cub->texture);
}
