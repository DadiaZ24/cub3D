/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:40:04 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/17 11:05:01 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_angle(t_game *game)
{
	if (game->scene->player_dir == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->scene->player_dir == 'S')
		game->player.angle = PI / 2;
	else if (game->scene->player_dir == 'E')
		game->player.angle = 0;
	else if (game->scene->player_dir == 'W')
		game->player.angle = PI;
}
