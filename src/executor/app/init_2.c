/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:12:27 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/17 11:06:29 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, t_img *img, char *path);

void	ft_load_textures(t_game *game)
{
	load_texture(game, &game->wall[N], game->scene->n_path);
	load_texture(game, &game->wall[S], game->scene->s_path);
	load_texture(game, &game->wall[E], game->scene->e_path);
	load_texture(game, &game->wall[W], game->scene->w_path);
}

static void	load_texture(t_game *game, t_img *img, char *path)
{
	img->width = 64;
	img->height = 64;
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->mlx_img)
		ft_end(16, NULL);
	img->addr = mlx_get_data_addr(img->mlx_img,
			&img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		ft_end(16, NULL);
}

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
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_hook(game->window, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->window, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->window, DestroyNotify, StructureNotifyMask, ft_exit, game);
	return (true);
}

void	init_player(t_game *game)
{
	game->player.rotating = 0;
	game->player.move_dir = 0;
	game->player.strafe_dir = 0;
	game->player.x = game->scene->spawn.x + 0.5;
	game->player.y = game->scene->spawn.y + 0.5;
	get_player_angle(game);
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}
