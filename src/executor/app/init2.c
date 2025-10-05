/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:33:12 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/05 14:33:12 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_game_data(t_game *game)
{
	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	game->game_img.mlx_img = mlx_new_image(game->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	game->game_img.addr = mlx_get_data_addr(game->game_img.mlx_img,
			&game->game_img.bpp, &game->game_img.line_len,
			&game->game_img.endian);
	if (!game->window || !game->game_img.mlx_img)
		return (false);
	mlx_put_image_to_window(game->mlx, game->window,
		game->game_img.mlx_img, 0, 0);
	if (!get_walls(game))
		return (false);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_hook(game->window, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->window, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->window, DestroyNotify, StructureNotifyMask, ft_exit, game);
	return (true);
}

bool	get_walls(t_game *game)
{
	game->wall[N].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_N,
			&game->wall[N].width, &game->wall[N].height);
	game->wall[S].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_S,
			&game->wall[S].width, &game->wall[S].height);
	game->wall[E].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_E,
			&game->wall[E].width, &game->wall[E].height);
	game->wall[W].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_W,
			&game->wall[W].width, &game->wall[W].height);
	if (!game->wall[N].mlx_img || !game->wall[S].mlx_img
		|| !game->wall[E].mlx_img
		|| !game->wall[W].mlx_img)
		return (false);
	return (true);
}

void	init_player(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	game->player.rotating = 0;
	game->player.move_dir = 0;
	game->player.strafe_dir = 0;
	game->player.x = game->scene->spawn.x + 0.5;
	game->player.y = game->scene->spawn.y + 0.5;
	get_player_angle(game, game->scene->spawn.x, game->scene->spawn.y);
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	while (game->scene->map[++y])
	{
		x = -1;
		while (game->scene->map[y][++x])
		{
		}
	}
}

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

t_scene	*ft_create_scene(char *path)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		ft_end(3, NULL);
	scene->floor_color = -1;
	scene->sky_color = -1;
	check_scene(path, scene);
	return (scene);
}
