/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdamnjan <vdamnjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:31:29 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/11 20:21:33 by vdamnjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/bonus_cub3d.h"

int	err(char *error)
{
	if (error)
		write(2, error, ft_strlen(error));
	return (1);
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
		exit(err(INVALID_ARGS_ERROR));
}

void	ft_check_map_name(char *map_path)
{
	int	i;

	i = 0;
	if (!map_path[i] || map_path[i] == '.')
		exit(err(INVALID_MAP_NAME_ERROR));
	while (map_path[i])
	{
		if (map_path[i] == '.' && !ft_strncmp(&map_path[i], ".cub", 5) && \
			map_path[i - 1] != '.')
			return ;
		i++;
	}
	exit(err(INVALID_MAP_EXTENSION_ERROR));
}
