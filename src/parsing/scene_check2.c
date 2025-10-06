/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:53:41 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/07 20:52:47 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map_characters(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_map_char(map[y][x]))
				ft_end(7, NULL);
			x++;
		}
		y++;
	}
}

void	validate_map(t_scene *scene)
{
	pad_map(scene);
	find_player(scene);
	check_closed_map(scene);
}

void	pad_map(t_scene *scene)
{
	int		y;
	int		len;
	char	*new_line;

	y = 0;
	while (scene->map[y])
	{
		len = ft_strlen(scene->map[y]);
		if (len < scene->map_size.x)
		{
			new_line = ft_calloc(scene->map_size.x + 1, sizeof(char));
			if (!new_line)
				ft_end(3, NULL);
			ft_memset(new_line, ' ', scene->map_size.x);
			ft_memcpy(new_line, scene->map[y], len);
			free(scene->map[y]);
			scene->map[y] = new_line;
		}
		y++;
	}
}

void	find_player(t_scene *scene)
{
	int		y;
	int		x;
	bool	found;

	found = false;
	y = 0;
	while (scene->map[y])
	{
		x = 0;
		while (scene->map[y][x])
		{
			if (ft_strchr("NSEW", scene->map[y][x]))
			{
				if (found)
					ft_end(10, NULL);
				set_spawn(scene, x, y, scene->map[y][x]);
				scene->map[y][x] = '0';
				found = true;
			}
			x++;
		}
		y++;
	}
	if (!found)
		ft_end(14, NULL);
}

void	check_closed_map(t_scene *scene)
{
	char		**copy;
	int			i;
	t_coords	coords;
	t_coords	max_coords;

	i = -1;
	coords.x = scene->spawn.x;
	coords.y = scene->spawn.y;
	max_coords.x = scene->map_size.x;
	max_coords.y = scene->map_size.y;
	copy = duplicate_map(scene);
	flood_fill(copy, &max_coords, coords.x, coords.y);
	while (copy[++i])
		free(copy[i]);
	free(copy);
}
