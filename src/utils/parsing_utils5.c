/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:54:28 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/16 11:35:21 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (true);
	return (false);
}

void	set_spawn(t_scene *scene, int x, int y, char dir)
{
	scene->spawn.x = x;
	scene->spawn.y = y;
	scene->player_dir = dir;
	printf("[DEBUG] Player spawn: (%d, %d), facing '%c'\n", x, y, dir);
}

char	**duplicate_map(t_game *game)
{
	char	**copy;
	int		i;
	t_scene	*scene;

	scene = game->scene;
	copy = malloc(sizeof(char *) * (scene->map_size.y + 1));
	if (!copy)
		ft_end(3, game);
	i = 0;
	while (i < scene->map_size.y)
	{
		copy[i] = ft_strdup(scene->map[i]);
		if (!copy[i])
		{
			free_array(copy, i);
			ft_end(6, game);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(t_fill_data *data, int x, int y, t_game *game)
{
	if (y < 0 || y >= data->max_y || x < 0 || x >= data->max_x)
		ft_end(7, game);
	if (data->map[y][x] == ' ' || data->map[y][x] == '\0')
		ft_end(13, game);
	if (data->map[y][x] == '1' || data->map[y][x] == 'F')
		return ;
	data->map[y][x] = 'F';
	flood_fill(data, x + 1, y, game);
	flood_fill(data, x - 1, y, game);
	flood_fill(data, x, y + 1, game);
	flood_fill(data, x, y - 1, game);
}

bool	validate_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}
