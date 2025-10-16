/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:23:09 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/05 14:23:09 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_front_right_y(t_game *game, double new_y, double y)
{
	if (y > 0)
	{
		if (game->scene->map[(int)(new_y + game->buffer)][(int)game->player.x]
			!= '1')
			game->player.y = new_y;
	}
	else if (y < 0)
	{
		if (game->scene->map[(int)(new_y - game->buffer)][(int)game->player.x]
			!= '1')
			game->player.y = new_y;
	}
}

void	move_front_right(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + x;
	new_y = game->player.y + y;
	if (x > 0)
	{
		if (game->scene->map[(int)game->player.y][(int)(new_x + game->buffer)]
			!= '1')
			game->player.x = new_x;
	}
	else if (x < 0)
	{
		if (game->scene->map[(int)game->player.y][(int)(new_x - game->buffer)]
			!= '1')
			game->player.x = new_x;
	}
	move_front_right_y(game, new_y, y);
}

static void	move_back_left_y(t_game *game, double new_y, double y)
{
	if (y > 0)
	{
		if (game->scene->map[(int)(new_y - game->buffer)][(int)game->player.x]
			!= '1')
			game->player.y = new_y;
	}
	else if (y < 0)
	{
		if (game->scene->map[(int)(new_y + game->buffer)][(int)game->player.x]
			!= '1')
			game->player.y = new_y;
	}
}

void	move_back_left(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + x;
	new_y = game->player.y + y;
	if (x > 0)
	{
		if (game->scene->map[(int)game->player.y][(int)(new_x - game->buffer)]
			!= '1')
			game->player.x = new_x;
	}
	else if (x < 0)
	{
		if (game->scene->map[(int)game->player.y][(int)(new_x + game->buffer)]
			!= '1')
			game->player.x = new_x;
	}
	move_back_left_y(game, new_y, y);
}
