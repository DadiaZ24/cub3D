/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:54:28 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/05 15:42:21 by pmachado         ###   ########.fr       */
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

char	**duplicate_map(t_scene *scene)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (scene->map_size.y + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < scene->map_size.y)
	{
		copy[i] = ft_strdup(scene->map[i]);
		if (!copy[i])
			ft_end(6, NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(char **map, int max_x, int max_y, int x, int y)
{
	if (y < 0 || y >= max_y || x < 0 || x >= max_x)
		ft_end(7, NULL);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		ft_end(13, NULL);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, max_x, max_y, x + 1, y);
	flood_fill(map, max_x, max_y, x - 1, y);
	flood_fill(map, max_x, max_y, x, y + 1);
	flood_fill(map, max_x, max_y, x, y - 1);
}
