/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:18:10 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/05 14:18:10 by ddias-fe         ###   ########.fr       */
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
	if (keycode == XK_w || keycode == XK_s)
		game->player.move_dir = 0;
	if (keycode == XK_a || keycode == XK_d)
		game->player.strafe_dir = 0;
	if (keycode == XK_Left || keycode == XK_Right)
		game->player.rotating = 0;
	return (0);
}
