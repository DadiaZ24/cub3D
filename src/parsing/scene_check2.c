/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:53:41 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/09 14:15:17 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map_characters(char **map)
{
	int	y;
	int	x;
	int	total;

	total = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_map_char(map[y][x]))
				ft_end(7, NULL);
			total++;
			x++;
		}
		y++;
	}
}

void	validate_map(t_scene *scene)
{
	find_player(scene);
	check_closed_map(scene);
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
					ft_end_scene(10, scene);
				set_spawn(scene, x, y, scene->map[y][x]);
				scene->map[y][x] = '0';
				found = true;
			}
			x++;
		}
		y++;
	}
	if (!found)
		ft_end_scene(14, scene);
}

void	check_closed_map(t_scene *scene)
{
	char		**copy;
	int			x;
	int			y;
	t_fill_data	data;

	x = scene->spawn.x;
	y = scene->spawn.y;
	replace_spaces_with_1s(scene->map);
	copy = duplicate_map(scene);
	data.map = copy;
	data.max_x = scene->map_size.x;
	data.max_y = scene->map_size.y;
	flood_fill(&data, x, y);
	free_array(copy, scene->map_size.y);
}
