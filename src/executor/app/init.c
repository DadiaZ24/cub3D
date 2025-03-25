#include "cub3d.h"

bool	init_game_data(t_game *game, t_data *data)
{
	game->data = data;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->game_img.mlx_img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->game_img.addr = mlx_get_data_addr(game->game_img.mlx_img, &game->game_img.bpp, &game->game_img.line_len, &game->game_img.endian);
	if (!game->window || !game->game_img.mlx_img)
		return (false);
	if (!get_walls(game))
		return (false);
	return (true);
}

bool	get_walls(t_game *game)
{
	game->wall[N].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_N, &game->wall[N].width, &game->wall[N].height);
	game->wall[S].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_S, &game->wall[S].width, &game->wall[S].height);
	game->wall[E].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_E, &game->wall[E].width, &game->wall[E].height);
	game->wall[W].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_W, &game->wall[W].width, &game->wall[W].height);
	if (!game->wall[N].mlx_img || !game->wall[S].mlx_img || !game->wall[E].mlx_img || !game->wall[W].mlx_img)
		return (false);
	return (true);
}
