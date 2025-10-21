/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:02:15 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/21 14:32:46 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	texture_map(t_game *game)
{
	if (!game->raycast.side)
		game->raycast.tex.wall_x = game->player.y + game->raycast.perp_wall_dist
			* game->raycast.ray_y;
	else
		game->raycast.tex.wall_x = game->player.x + game->raycast.perp_wall_dist
			* game->raycast.ray_x;
	game->raycast.tex.wall_x -= floor(game->raycast.tex.wall_x);
	game->raycast.tex.texture_x = game->raycast.tex.wall_x * 64;
	if ((!game->raycast.side && game->raycast.ray_x < 0)
		|| (game->raycast.side && game->raycast.ray_y > 0))
		game->raycast.tex.texture_x = 64 - game->raycast.tex.texture_x - 1;
	game->raycast.tex.step = 1.0 * 64 / game->raycast.line_height;
	game->raycast.tex.texture_pos = (game->raycast.start - SCREEN_HEIGHT / 2
			+ game->raycast.line_height / 2) * game->raycast.tex.step;
}

static void	draw_column(t_game *game, int x)
{
	int	y;
	int	color;

	y = game->raycast.start - 1;
	texture_map(game);
	while (++y < game->raycast.end)
	{
		game->raycast.tex.texture_y = (int)game->raycast.tex.texture_pos
			& (64 - 1);
		game->raycast.tex.texture_pos += game->raycast.tex.step;
		color = get_color(game, game->raycast.tex.texture_x,
				game->raycast.tex.texture_y, game->raycast.wall_dir);
		put_pixel(game, x, y, color);
	}
}

static void	init_raycast(t_game *game)
{
	if (game->raycast.ray_x < 0)
	{
		game->raycast.step_x = -1;
		game->raycast.side_x = (game->player.x - game->raycast.map_x)
			* game->raycast.delta_x;
	}
	else
	{
		game->raycast.step_x = 1;
		game->raycast.side_x = (game->raycast.map_x + 1.0 - game->player.x)
			* game->raycast.delta_x;
	}
	if (game->raycast.ray_y < 0)
	{
		game->raycast.step_y = -1;
		game->raycast.side_y = (game->player.y - game->raycast.map_y)
			* game->raycast.delta_y;
	}
	else
	{
		game->raycast.step_y = 1;
		game->raycast.side_y = (game->raycast.map_y + 1 - game->player.y)
			* game->raycast.delta_y;
	}
}

void	setup_raycast(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->raycast.ray_x = cos(game->player.angle)
		+ (-sin(game->player.angle) * FOV) * camera_x;
	game->raycast.ray_y = sin(game->player.angle)
		+ (cos(game->player.angle) * FOV) * camera_x;
	game->raycast.map_x = (int)game->player.x;
	game->raycast.map_y = (int)game->player.y;
	if (game->raycast.ray_x == 0)
		game->raycast.delta_x = INT_MAX;
	else
		game->raycast.delta_x = fabs(1 / game->raycast.ray_x);
	if (game->raycast.ray_y == 0)
		game->raycast.delta_y = INT_MAX;
	else
		game->raycast.delta_y = fabs(1 / game->raycast.ray_y);
	game->raycast.hit = false;
}

void	raycast(t_game *game)
{
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		setup_raycast(game, x);
		init_raycast(game);
		dda(game);
		calculate_distance(game);
		draw_column(game, x);
	}
}
