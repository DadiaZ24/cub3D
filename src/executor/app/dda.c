/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:15:44 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/05 14:15:44 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_helper(t_game *game)
{
	if (game->raycast.side_x < game->raycast.side_y)
	{
		game->raycast.side_x += game->raycast.delta_x;
		game->raycast.map_x += game->raycast.step_x;
		game->raycast.side = false;
	}
	else
	{
		game->raycast.side_y += game->raycast.delta_y;
		game->raycast.map_y += game->raycast.step_y;
		game->raycast.side = true;
	}
}

static void	dda_hit(t_game *game)
{
	if (!game->raycast.side)
	{
		if (game->raycast.ray_x > 0)
			game->raycast.wall_dir = W;
		else
			game->raycast.wall_dir = E;
	}
	else
	{
		if (game->raycast.ray_y > 0)
			game->raycast.wall_dir = N;
		else
			game->raycast.wall_dir = S;
	}
}

void	dda(t_game *game)
{
	while (!game->raycast.hit)
	{
		dda_helper(game);
		if (game->raycast.map_y < 0 || game->raycast.map_y
			>= game->scene->map_size.y
			|| game->raycast.map_x < 0 || game->raycast.map_x
			>= game->scene->map_size.x)
			break ;
		if (game->scene->map[game->raycast.map_y][game->raycast.map_x] == '1')
		{
			game->raycast.hit = true;
			dda_hit(game);
		}
	}
}

void	calculate_distance(t_game *game)
{
	if (!game->raycast.side)
		game->raycast.perp_wall_dist = (game->raycast.map_x - game->player.x
				+ (1 - game->raycast.step_x) / 2.0) / game->raycast.ray_x;
	else
		game->raycast.perp_wall_dist = (game->raycast.map_y - game->player.y
				+ (1 - game->raycast.step_y) / 2.0) / game->raycast.ray_y;
	game->raycast.line_height = (int)(SCREEN_HEIGHT
			/ game->raycast.perp_wall_dist);
	game->raycast.start = -game->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->raycast.start < 0)
		game->raycast.start = 0;
	game->raycast.end = game->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->raycast.end >= SCREEN_HEIGHT)
		game->raycast.end = SCREEN_HEIGHT - 1;
}
