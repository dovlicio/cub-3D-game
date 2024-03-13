/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:15:15 by jlomic            #+#    #+#             */
/*   Updated: 2024/03/13 18:01:39 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_textures(t_cub *cub, t_img *texture)
{
	mlx_destroy_image(cub->mlx, texture[0].img);
	mlx_destroy_image(cub->mlx, texture[1].img);
	mlx_destroy_image(cub->mlx, texture[2].img);
	mlx_destroy_image(cub->mlx, texture[3].img);
}

void	check_textures(t_cub *cub, t_img *texture)
{
	if (!texture[0].img || !texture[1].img
		|| !texture[2].img || !texture[3].img)
	{
		if (texture[0].img)
			mlx_destroy_image(cub->mlx, texture[0].img);
		if (texture[1].img)
			mlx_destroy_image(cub->mlx, texture[1].img);
		if (texture[2].img)
			mlx_destroy_image(cub->mlx, texture[2].img);
		if (texture[3].img)
			mlx_destroy_image(cub->mlx, texture[3].img);
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		free(cub->buffer);
		ft_clean_parse(cub->parse, "Failed to initialize images.\n");
	}
	return ;
}

void	check_addr(t_cub *cub, t_img *texture)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!(texture[i].addr))
			fail_exit(cub, "Error\nFailed to get addr of image\n");
		i++;
	}
}

void	initialize_textures(t_cub *cub)
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
	check_textures(cub, cub->texture);
	texture[0].addr = mlx_get_data_addr(texture[0].img, &texture[0]
			.bits_per_pixel, &texture[0].size_line, &texture[0].endian);
	texture[1].addr = mlx_get_data_addr(texture[1].img, &texture[1]
			.bits_per_pixel, &texture[1].size_line, &texture[1].endian);
	texture[2].addr = mlx_get_data_addr(texture[2].img, &texture[2]
			.bits_per_pixel, &texture[2].size_line, &texture[2].endian);
	texture[3].addr = mlx_get_data_addr(texture[3].img, &texture[3]
			.bits_per_pixel, &texture[3].size_line, &texture[3].endian);
	check_addr(cub, texture);
}
