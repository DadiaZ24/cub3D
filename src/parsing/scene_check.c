/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:40:15 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/12 21:17:13 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// printf("[DEBUG] n_path: %s\n", scene->n_path);
// printf("[DEBUG] s_path: %s\n", scene->s_path);
// printf("[DEBUG] w_path: %s\n", scene->w_path);
// printf("[DEBUG] e_path: %s\n", scene->e_path);
// printf("[DEBUG] floor_color: %d\n", scene->floor_color);
// printf("[DEBUG] sky_color: %d\n", scene->sky_color);
// for (int j = 0; scene->map[j]; j++)
// 	printf("[POST-MAP] %s\n", scene->map[j]);
// printf("[DEBUG] Mapa Valido :)\n");
void	check_scene(char *path, t_game *game)
{
	read_scene(path, game);
	check_for_empty(game);
	validate_elements(game);
	separate_map(game);
	validate_map_characters(game);
	validate_map(game);
}

void	read_scene(char *path, t_game *game)
{
	int		fd;
	int		line_count;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_end(4, game);
	line_count = ft_count_lines(path);
	game->scene->raw_lines = ft_calloc(line_count + 1, sizeof(char *));
	if (!game->scene->raw_lines)
		ft_end(3, game);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->scene->raw_lines[i] = process_scene_line(line);
		free(line);
		if (game->scene->raw_lines[i])
			i++;
		line = get_next_line(fd);
	}
	game->scene->raw_lines[i] = NULL;
	close(fd);
}

void	check_for_empty(t_game *game)
{
	if (!game->scene->raw_lines || !game->scene->raw_lines[0])
		ft_end(12, game);
}

void	separate_map(t_game *game)
{
	int	start;
	int	count;

	start = get_map_start_index(game->scene->raw_lines);
	if (start == -1)
		ft_end(8, game);
	count = count_map_lines(game->scene->raw_lines + start);
	game->scene->map_size.y = count;
	copy_map_lines(game, start, count);
	game->scene->map_size.x = ft_get_max_line_length(game->scene->map);
}

void	validate_elements(t_game *game)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (game->scene->raw_lines[i])
	{
		trimmed = ft_strtrim(game->scene->raw_lines[i], " \t");
		if (trimmed[0] != '\0')
		{
			if (ft_is_map_line(trimmed) && all_elements_found(game->scene))
			{
				free(trimmed);
				break ;
			}
			parse_textures(game, trimmed);
		}
		free(trimmed);
		i++;
	}
	if (!game->scene->n_path || !game->scene->s_path || !game->scene->e_path
		|| !game->scene->w_path || game->scene->floor_color == -1
		|| game->scene->sky_color == -1)
		ft_end(9, game);
}
