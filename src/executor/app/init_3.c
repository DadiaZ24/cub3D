/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:40:04 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/16 12:40:13 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_angle(t_game *game, int x, int y)
{
	if (game->scene->map[y][x] == 'N')
		game->player.angle = N;
	else if (game->scene->map[y][x] == 'S')
		game->player.angle = S;
	else if (game->scene->map[y][x] == 'E')
		game->player.angle = E;
	else if (game->scene->map[y][x] == 'W')
		game->player.angle = W;
}
