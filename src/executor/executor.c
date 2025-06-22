/* #include "cub3d.h"

bool executor(t_game *game, t_data *data)
{
	if (!init_game_data(game, data))
		return (printf("FIX THIS ERROR (INIT GAME DATA)"), false);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	return (true);
}

int	render(t_game *game)
{
	if (!render_background(game))
		return (printf("FIX THIS ERROR (RENDER BACKGROUND)"), 0);
	mlx_put_image_to_window(game->mlx, game->window, game->game_img.mlx_img, 0, 0);
	return (1);
}
 */