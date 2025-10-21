/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:18:10 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/21 14:32:47 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		ft_exit(game);
	if (keycode == XK_w)
		game->player.move_dir = 1;
	if (keycode == XK_s)
		game->player.move_dir = -1;
	if (keycode == XK_a)
		game->player.strafe_dir = -1;
	if (keycode == XK_d)
		game->player.strafe_dir = 1;
	if (keycode == XK_Left)
		game->player.rotating = -1;
	if (keycode == XK_Right)
		game->player.rotating = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w && game->player.move_dir == 1)
		game->player.move_dir = 0;
	if (keycode == XK_s && game->player.move_dir == -1)
		game->player.move_dir = 0;
	if (keycode == XK_a && game->player.strafe_dir == -1)
		game->player.strafe_dir = 0;
	if (keycode == XK_d && game->player.strafe_dir == 1)
		game->player.strafe_dir = 0;
	if (keycode == XK_Left && game->player.rotating == -1)
		game->player.rotating = 0;
	if (keycode == XK_Right && game->player.rotating == 1)
		game->player.rotating = 0;
	return (0);
}
