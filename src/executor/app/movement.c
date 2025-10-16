/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:29:01 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/16 19:41:02 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_game *game, double angle)
{
	game->player.angle += angle;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	else if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

void	movement(t_game *game)
{
	double	move_x;
	double	move_y;
	double	strafe_x;
	double	strafe_y;

	move_x = cos(game->player.angle) * MOVE_SPEED;
	move_y = sin(game->player.angle) * MOVE_SPEED;
	strafe_x = cos(game->player.angle + PI / 2) * MOVE_SPEED;
	strafe_y = sin(game->player.angle + PI / 2) * MOVE_SPEED;
	if (game->player.move_dir != 0)
		move_front_right(game, move_x * game->player.move_dir, move_y
			* game->player.move_dir);
	if (game->player.strafe_dir != 0)
		move_front_right(game, strafe_x * game->player.strafe_dir, strafe_y
			* game->player.strafe_dir);
	if (game->player.rotating == 1)
		rotate(game, ROTATE_SPEED);
	if (game->player.rotating == -1)
		rotate(game, -ROTATE_SPEED);
}
