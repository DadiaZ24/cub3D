/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:17:57 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/04 13:18:41 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//----------separate_map-------------//

int	get_map_start_index(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (ft_is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

bool	ft_is_map_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '0' && *line != '1'
			&& *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W')
			return (false);
		line++;
	}
	return (true);
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
		ft_end(3, scene);
	i = 0;
	while (i < count)
	{
		scene->map[i] = ft_strdup(scene->raw_lines[start + i]);
		if (!scene->map[i])
			ft_end(3, scene);
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
