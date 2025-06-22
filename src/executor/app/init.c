/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:43:31 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/05 16:43:22 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, t_img *img, char *path);

t_game	*ft_init_game(char *map_path)
{
	t_game	*game;
	
	game = ft_create_game(); //alocar t_game
	game->scene = ft_create_scene(map_path); //alocar t_scene
	ft_init_mlx(game); //inicializar mlx
	ft_load_textures(game);
	return (game);
}

t_game	*ft_create_game(void)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	if (!game)
		ft_end(3, NULL);
	game->scene = NULL;
	game->mlx = NULL;
	game->window = NULL;
	return (game);	
}
void	ft_init_mlx(t_game *game)
{
	int	i;

	i = 0;
	game->game_img.mlx_img = NULL;
	game->game_img.addr = NULL;
	game->game_img.bpp = 0;
	game->game_img.line_len = 0;
	game->game_img.endian = 0;
	game->game_img.width = 0;
	game->game_img.height = 0;
	while (i < 4)
	{
		game->wall[i].mlx_img = NULL;
		game->wall[i].addr = NULL;
		game->wall[i].bpp = 0;
		game->wall[i].line_len = 0;
		game->wall[i].endian = 0;
		game->wall[i].width = 0;
		game->wall[i].height = 0;
		i++;
	}
}

t_scene	*ft_create_scene(char *path)
{
	t_scene	*scene;
	
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		ft_end(3, NULL);
	scene->floor_color = -1; //inicializar cores
	scene->sky_color = -1; //inicializar cores
	check_scene(path, scene); //ler o ficheiro .cub e fazer o parsing
	return (scene);
}

void	ft_load_textures(t_game *game)
{
	load_texture(game, &game->wall[N], game->scene->n_path);
	load_texture(game, &game->wall[S], game->scene->s_path);
	load_texture(game, &game->wall[E], game->scene->e_path);
	load_texture(game, &game->wall[W], game->scene->w_path);
}

static void	load_texture(t_game *game, t_img *img, char *path)
{
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->mlx_img)
		ft_end(16, NULL);
	img->addr = mlx_get_data_addr(img->mlx_img,
			&img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		ft_end(16, NULL);
}

// bool	init_game_data(t_game *game, t_data *data)
// {
// 	game->data = data;
// 	game->mlx = mlx_init();
// 	if (!game->mlx)
// 		return (false);
// 	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
// 	game->game_img.mlx_img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	game->game_img.addr = mlx_get_data_addr(game->game_img.mlx_img, &game->game_img.bpp, &game->game_img.line_len, &game->game_img.endian);
// 	if (!game->window || !game->game_img.mlx_img)
// 		return (false);
// 	if (!get_walls(game))
// 		return (false);
// 	return (true);
// }

// bool	get_walls(t_game *game)
// {
// 	game->wall[N].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_N, &game->wall[N].width, &game->wall[N].height);
// 	game->wall[S].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_S, &game->wall[S].width, &game->wall[S].height);
// 	game->wall[E].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_E, &game->wall[E].width, &game->wall[E].height);
// 	game->wall[W].mlx_img = mlx_xpm_file_to_image(game->mlx, TEXTURE_W, &game->wall[W].width, &game->wall[W].height);
// 	if (!game->wall[N].mlx_img || !game->wall[S].mlx_img || !game->wall[E].mlx_img || !game->wall[W].mlx_img)
// 		return (false);
// 	return (true);
// }
