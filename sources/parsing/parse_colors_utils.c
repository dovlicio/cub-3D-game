/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdamnjan <vdamnjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:18:25 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/05 12:47:17 by vdamnjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_set_tmp(t_parse *parse, int start, int *j, char *str)
{
	parse->tmp = ft_substr(str, start, *j - start);
	if (!parse->tmp)
		ft_clean_parse(parse, MALLOC_FAILED_ERROR);
	while (str[*j] && str[*j] == ' ')
		(*j)++;
	if (str[*j] && str[*j] != '\n')
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
}
