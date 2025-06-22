/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:17:57 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/09 17:10:24 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//----------separate_map-------------//

int	get_map_start_index(char **lines)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (lines[i])
	{
		trimmed = ft_strtrim(lines[i], " \t");
		if (ft_is_map_line(trimmed))
		{
			free(trimmed);
			return (i);
		}
		free(trimmed);
		i++;
	}
	return (-1);
}

bool	ft_is_map_line(char *line)
{
	int		i;
	bool	has_content;

	i = 0;
	has_content = false;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (false);
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			has_content = true;
		i++;
	}
	return (has_content);
}

int	count_map_lines(char **lines)
{
	int	count;

	count = 0;
	while (lines[count])
		count++;
	return (count);
}

void	copy_map_lines(t_scene *scene, int start, int count)
{
	int	i;

	scene->map = ft_calloc(count + 1, sizeof(char *));
	if (!scene->map)
		ft_end(3, NULL);
	i = 0;
	while (i < count)
	{
		scene->map[i] = ft_strdup(scene->raw_lines[start + i]);
		if (!scene->map[i])
			ft_end(3, NULL);
		i++;
	}
	scene->map[i] = NULL;
}

int	ft_get_max_line_length(char **map)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}
