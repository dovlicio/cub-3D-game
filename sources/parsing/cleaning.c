/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:27:42 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/07 22:16:25 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
			free(matrix[i++]);
		free(matrix);
	}
}

void	clean_ft_clean_parse(t_parse *parse, char *error)
{
	if (parse->north_path)
		free(parse->north_path);
	if (parse->west_path)
		free(parse->west_path);
	if (parse->east_path)
		free(parse->east_path);
	if (parse->south_path)
		free(parse->south_path);
	if (parse->ceiling_color)
		free(parse->ceiling_color);
	if (parse->floor_color)
		free(parse->floor_color);
	free_matrix(parse->map);
	free_matrix(parse->copy);
	if (parse->tmp)
		free(parse->tmp);
	if (error)
		write(1, error, ft_strlen(error));
	exit(0);
}

void	ft_clean_parse(t_parse *parse, char *error)
{
	if (parse->north_path)
		free(parse->north_path);
	if (parse->west_path)
		free(parse->west_path);
	if (parse->east_path)
		free(parse->east_path);
	if (parse->south_path)
		free(parse->south_path);
	if (parse->ceiling_color)
		free(parse->ceiling_color);
	if (parse->floor_color)
		free(parse->floor_color);
	free_matrix(parse->map);
	free_matrix(parse->copy);
	if (parse->tmp)
		free(parse->tmp);
	exit(err(error));
}

void	free_new(t_parse *parse, int i, char *new)
{
	while (parse->copy[i])
	{
		free(parse->copy[i]);
		parse->copy[i++] = NULL;
	}
	free(new);
}
