/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:28:56 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/16 19:49:12 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replace_spaces_with_1s(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ' || map[y][x] == '\t')
				map[y][x] = '1';
			x++;
		}
		y++;
	}
}

char	*process_scene_line(char *line)
{
	char	*clean;
	char	*trimmed;
	int		i;

	clean = spaces_for_tabs(line);
	trimmed = ft_strtrim(clean, "\n");
	if (clean != line)
		free(clean);
	i = 0;
	while (trimmed[i])
	{
		if (trimmed[i] != ' ' && trimmed[i] != '\t')
			return (trimmed);
		i++;
	}
	free(trimmed);
	return (NULL);
}

bool	all_elements_found(t_scene *scene)
{
	return (scene->n_path && scene->s_path && scene->e_path && scene->w_path
		&& scene->floor_color != -1 && scene->sky_color != -1);
}
