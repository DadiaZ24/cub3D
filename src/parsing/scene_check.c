/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:40:15 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/09 14:27:25 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_scene(char *path, t_scene *scene)
{
	read_scene(path, scene);
	check_for_empty(scene);
	validate_elements(scene);
	printf("[DEBUG] n_path: %s\n", scene->n_path);
	printf("[DEBUG] s_path: %s\n", scene->s_path);
	printf("[DEBUG] w_path: %s\n", scene->w_path);
	printf("[DEBUG] e_path: %s\n", scene->e_path);
	printf("[DEBUG] floor_color: %d\n", scene->floor_color);
	printf("[DEBUG] sky_color: %d\n", scene->sky_color);
	separate_map(scene);
	validate_map_characters(scene->map);
	validate_map(scene);
	for (int j = 0; scene->map[j]; j++)
		printf("[POST-MAP] %s\n", scene->map[j]);
	printf("[DEBUG] Mapa Valido :)\n");
}

void	read_scene(char *path, t_scene *scene)
{
	int		fd;
	int		line_count;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_end_scene(4, scene);
	line_count = ft_count_lines(path);
	scene->raw_lines = ft_calloc(line_count + 1, sizeof(char *));
	if (!scene->raw_lines)
		ft_end_scene(3, scene);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		scene->raw_lines[i] = process_scene_line(line);
		free(line);
		if (scene->raw_lines[i])
			i++;
		line = get_next_line(fd);
	}
	scene->raw_lines[i] = NULL;
	close(fd);
}

void	check_for_empty(t_scene *scene)
{
	if (!scene->raw_lines || !scene->raw_lines[0])
		ft_end_scene(12, scene);
}

void	separate_map(t_scene *scene)
{
	int	start;
	int	count;

	start = get_map_start_index(scene->raw_lines);
	if (start == -1)
		ft_end_scene(8, scene);
	count = count_map_lines(scene->raw_lines + start);
	scene->map_size.y = count;
	copy_map_lines(scene, start, count);
	scene->map_size.x = ft_get_max_line_length(scene->map);
}

void	validate_elements(t_scene *scene)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (scene->raw_lines[i])
	{
		trimmed = ft_strtrim(scene->raw_lines[i], " \t");
		if (trimmed[0] != '\0')
		{
			if (ft_is_map_line(trimmed) && all_elements_found(scene))
			{
				free(trimmed);
				break ;
			}
			parse_textures(scene, trimmed);
		}
		free(trimmed);
		i++;
	}
	if (!scene->n_path || !scene->s_path || !scene->e_path || !scene->w_path
		|| scene->floor_color == -1 || scene->sky_color == -1)
		ft_end_scene(9, scene);
}
