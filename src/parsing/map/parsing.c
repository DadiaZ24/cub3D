/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:41:10 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/06/02 21:33:14 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_validate_args(int ac, char **av)
{
	if (ac != 2)
		ft_end(1, NULL);
	if (ft_strlen(av[1]) < 4
		|| ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		ft_end(2, NULL);
	return (true);
	//ERROR_FILE_EXTENSION
}

void	check_scene(char *path, t_scene *scene)
{
	read_scene(path, scene);					// opens + reads .cub
	check_for_empty(scene);						// empty lines?
	separate_map(scene);						// extract map
	validate_elements(scene);					// all metadata filled?
	validate_map_characters(scene->map);		// only valid characters
	validate_map(scene);						// check closure, player
}

void	read_scene(char *path, t_scene *scene)
{
	int		fd;
	int		line_count;
	int		i;
	char	*line;
	char	*clean;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_end(4, scene);
	line_count = ft_count_lines(path);
	scene->raw_lines = ft_calloc(line_count + 1, sizeof(char *));
	if (!scene->raw_lines)
		ft_end(ERROR_MALLOC, scene);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		clean = replace_tabs(line);
		scene->raw_lines[i] = ft_strtrim(clean, "\n");
		free(clean);
		free(line);
		if (!scene->raw_lines[i])
			ft_end(ERROR_MALLOC, scene);
		i++;
	}
	scene->raw_lines[i] = NULL;
	close(fd);
}

void	check_for_empty(t_scene *scene)
{
	if (!scene->raw_lines || !scene->raw_lines[0])
		ft_end(ERROR_EMPTY_FILE, scene);
}

void	separate_map(t_scene *scene)
{
	int	start;
	int	count;

	start = get_map_start_index(scene->raw_lines);
	if (start == -1)
		ft_end(ERROR_NO_MAP, scene);
	count = count_map_lines(scene->raw_lines + start);
	scene->map_size.y = count;
	copy_map_lines(scene, start, count);
	scene->map_size.x = ft_get_max_line_length(scene->map);
}

