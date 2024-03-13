/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlomic <jlomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:52:07 by vdamnjan          #+#    #+#             */
/*   Updated: 2024/03/13 17:24:25 by jlomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_realocate_copy(t_parse *parse)
{
	int		i;
	char	*new;

	i = 0;
	while (parse->copy[i])
	{
		if (((int)ft_strlen(parse->copy[i]) - 1) < parse->map_w)
		{
			new = ft_calloc(parse->map_w + 1, sizeof(char));
			if (!new)
				ft_clean_parse(parse, MALLOC_FAILED_ERROR);
			ft_copy_row(parse, new, i);
			free(parse->copy[i]);
			parse->copy[i] = ft_strdup(new);
			if (!parse->copy[i])
				(free_new(parse, i + 1, new), \
				ft_clean_parse(parse, MALLOC_FAILED_ERROR));
			free(new);
		}
		i++;
	}
}

static void	ft_import_map(t_parse *parse, char *temp, int i)
{
	parse->map = ft_split(&temp[i], '\n');
	if (!parse->map)
		ft_clean_parse(parse, MALLOC_FAILED_ERROR);
	parse->copy = ft_split(&temp[i], '\n');
	if (!parse->copy)
		ft_clean_parse(parse, MALLOC_FAILED_ERROR);
	ft_get_player_position(parse);
	ft_get_map_size(parse);
	ft_realocate_copy(parse);
	flood_fill(parse, parse->copy, parse->pos_y, parse->pos_x);
	if (parse->error == 1)
		ft_clean_parse(parse, INVALID_MAP_FILE_ERROR);
}

static void	ft_import_data(t_parse *parse, char *temp)
{
	int		i;
	char	*str;

	str = temp;
	i = 0;
	while (str[i])
	{
		if (ft_check_row(parse, &str[i]))
			break ;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '\n')
		{
			i++;
			continue ;
		}
		ft_loop_data(parse, &str[i], &i);
		i++;
	}
	ft_check_data(parse);
	ft_check_map(parse, temp, i);
	ft_import_map(parse, temp, i);
}

static void	ft_read_map(t_parse *parse)
{
	int		buffer_size;
	int		fd;
	char	temp[150000];

	fd = open(parse->map_path, O_RDONLY);
	if (fd == -1)
		exit((err(FILE_OPEN_FAILED_ERROR), err(parse->map_path), err("'\n")));
	buffer_size = read(fd, temp, 150000);
	if (buffer_size >= 149999)
		(close(fd), exit(err(FAILE_READING_FAIL_ERROR)));
	if (buffer_size == -1)
		(close(fd), exit(err(FAILE_READING_FAIL_ERROR)));
	close(fd);
	temp[buffer_size] = '\0';
	ft_import_data(parse, temp);
}

void	ft_parse_map(int argc, char *map_path, t_parse *parse)
{
	ft_check_argc(argc);
	ft_check_map_name(map_path);
	parse->map_path = map_path;
	ft_read_map(parse);
}
