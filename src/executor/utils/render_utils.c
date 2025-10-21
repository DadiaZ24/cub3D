/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:55:33 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/21 14:33:43 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	render_background(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			put_pixel(game, x, y, game->scene->sky_color);
	}
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			put_pixel(game, x, y, game->scene->floor_color);
	}
	return (true);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	offset = (y * game->game_img.line_len) + (x * (game->game_img.bpp / 8));
	*(unsigned int *)(game->game_img.addr + offset) = color;
}

int	get_color(t_game *game, int x, int y, int i)
{
	return (*(int *)(game->wall[i].addr + (y * game->wall[i].line_len
			+ x * (game->wall[i].bpp / 8))));
}
