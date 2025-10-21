/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:53:41 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/21 14:53:55 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map_characters(t_game *game)
{
	int		y;
	int		x;
	int		total;
	char	**map;

	map = game->scene->map;
	total = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_map_char(map[y][x]))
				ft_end(7, game);
			total++;
			x++;
		}
		y++;
	}
}

void	validate_map(t_game *game)
{
	find_player(game);
	check_player_space(game);
	check_closed_map(game);
}

void	find_player(t_game *game)
{
	int		y;
	int		x;
	bool	found;

	found = false;
	y = 0;
	while (game->scene->map[y])
	{
		x = 0;
		while (game->scene->map[y][x])
		{
			if (ft_strchr("NSEW", game->scene->map[y][x]))
			{
				if (found)
					ft_end(10, game);
				set_spawn(game->scene, x, y, game->scene->map[y][x]);
				game->scene->map[y][x] = '0';
				found = true;
			}
			x++;
		}
		y++;
	}
	if (!found)
		ft_end(14, game);
}

void	check_closed_map(t_game *game)
{
	char		**copy;
	int			x;
	int			y;

	x = game->scene->spawn.x;
	y = game->scene->spawn.y;
	replace_spaces_with_1s(game->scene->map);
	copy = duplicate_map(game);
	game->scene->data.map = copy;
	game->scene->data.max_x = game->scene->map_size.x;
	game->scene->data.max_y = game->scene->map_size.y;
	flood_fill(x, y, game);
	free_array(copy, game->scene->map_size.y);
}

void	check_player_space(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	x = game->scene->spawn.x;
	y = game->scene->spawn.y;
	map = game->scene->map;
	if (y == 0 || x == 0
		|| y == game->scene->map_size.y - 1
		|| x == game->scene->map_size.x - 1)
		ft_end(19, game);
	if (map[y - 1][x] == '1' && map[y + 1][x] == '1'
		&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
		ft_end(18, game);
}
