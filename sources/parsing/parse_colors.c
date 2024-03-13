/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:10:04 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/04 15:11:27 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_set_color(t_parse *parse, char **nums, int t)
{
	if (t == 5)
	{
		parse->ceiling_color[0] = ft_atoi(nums[0]);
		parse->ceiling_color[1] = ft_atoi(nums[1]);
		parse->ceiling_color[2] = ft_atoi(nums[2]);
		free_matrix(nums);
		if (parse->ceiling_color[0] > 255 || parse->ceiling_color[1] > 255 || \
			parse->ceiling_color[2] > 255)
			ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
		return ;
	}
	parse->floor_color[0] = ft_atoi(nums[0]);
	parse->floor_color[1] = ft_atoi(nums[1]);
	parse->floor_color[2] = ft_atoi(nums[2]);
	free_matrix(nums);
	if (parse->floor_color[0] > 255 || parse->floor_color[1] > 255 || \
		parse->floor_color[2] > 255)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
}

static void	ft_check_nums(t_parse *parse, char **nums, int t)
{
	int	i;
	int	j;

	i = 0;
	while (nums[i])
	{
		j = 0;
		while (nums[i][j])
			if (!ft_isdigit(nums[i][j++]))
				(free_matrix(nums), \
				ft_clean_parse(parse, INVALID_MAP_FILE_ERROR));
		i++;
	}
	if (ft_strlen(nums[0]) > 3 || ft_strlen(nums[1]) > 3 || \
		ft_strlen(nums[2]) > 3)
		(free_matrix(nums), ft_clean_parse(parse, INVALID_MAP_FILE_ERROR));
	ft_set_color(parse, nums, t);
}

static void	ft_check_commas(t_parse *parse, char *tmp, int t)
{
	int		i;
	int		j;
	char	**nums;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == ',' && i != 0 && ft_isdigit(tmp[i - 1]) && \
			tmp[i + 1] && ft_isdigit(tmp[i + 1]))
			j++;
		i++;
	}
	if (j != 2)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	nums = ft_split(tmp, ',');
	if (!nums)
		ft_clean_parse(parse, MALLOC_FAILED_ERROR);
	ft_check_nums(parse, nums, t);
}

static void	ft_colors_check(t_parse *parse, int *i, int j, int c)
{
	(ft_check_commas(parse, parse->tmp, c), free(parse->tmp));
	parse->tmp = NULL;
	*i += j;
}

void	ft_handle_colors(t_parse *parse, char *str, int *i, int c)
{
	int		j;
	int		**ptr;
	int		start;

	ptr = (int **)ft_set_ptr(parse, c);
	if (*ptr)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	j = 0;
	while (str[j] != ' ')
		j++;
	while (str[j] && str[j] == ' ')
		j++;
	if (str[j] && str[j] != '\n')
	{
		start = j;
		while (str[j] && !ft_strchr(" \n", str[j]))
			j++;
		*ptr = ft_calloc(3, sizeof(int));
		if (!(*ptr))
			ft_clean_parse(parse, MALLOC_FAILED_ERROR);
		ft_set_tmp(parse, start, &j, str);
	}
	if (!(*ptr))
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
	ft_colors_check(parse, i, j, c);
}
