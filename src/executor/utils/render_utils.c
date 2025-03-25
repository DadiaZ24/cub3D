#include "cub3d.h"

bool	render_background(t_game *game)
{
	int x;
	int y;

	y = -1;
	while (++y < SCREEN_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			put_pixel(game, x, y, game->data->sky_color);
	}
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			put_pixel(game, x, y, game->data->floor_color);
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
