/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:54:28 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/21 15:05:16 by ddias-fe         ###   ########.fr       */
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

void	flood_fill(int x, int y, t_game *game)
{
	if (y < 0 || y >= game->scene->data.max_y || x < 0
		|| x >= game->scene->data.max_x)
	{
		free_duplicate_map(game->scene->data.map);
		ft_end(7, game);
	}
	if (game->scene->data.map[y][x] == ' '
		|| game->scene->data.map[y][x] == '\0')
	{
		free_duplicate_map(game->scene->data.map);
		ft_end(13, game);
	}
	if (game->scene->data.map[y][x] == '1'
		|| game->scene->data.map[y][x] == 'F')
		return ;
	game->scene->data.map[y][x] = 'F';
	flood_fill(x + 1, y, game);
	flood_fill(x - 1, y, game);
	flood_fill(x, y + 1, game);
	flood_fill(x, y - 1, game);
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
