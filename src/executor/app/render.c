/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:58:25 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/21 14:32:44 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_loop(t_game *game)
{
	movement(game);
	render_background(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->window,
		game->game_img.mlx_img, 0, 0);
	return (0);
}
