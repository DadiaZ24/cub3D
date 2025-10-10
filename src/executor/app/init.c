/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:43:31 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/09 22:42:46 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, t_img *img, char *path);

t_game	*ft_init_game(char *map_path)
{
	t_game	*game;

	game = ft_create_game();
	game->scene = ft_create_scene(map_path, game);
	printf("Parsing feito :)\n");
	ft_init_mlx(game);
	printf("mlx iniciada :) \n");
	ft_load_textures(game);
	printf("Texturas carregadas :) \n");
	return (game);
}

t_game	*ft_create_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_end(3, NULL);
	game->scene = NULL;
	game->mlx = NULL;
	game->window = NULL;
	return (game);
}

t_scene	*ft_create_scene(char *path, t_game *game)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		ft_end(3, game);
	scene->floor_color = -1;
	scene->sky_color = -1;
	game->scene = scene;
	check_scene(path, game);
	return (scene);
}

void	ft_init_mlx(t_game *game)
{
	int	i;

	i = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_end(5, NULL);
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

void	ft_load_textures(t_game *game)
{
	load_texture(game, &game->wall[N], game->scene->n_path);
	printf("[DEBUG] textura North carregada: %s\n", game->scene->n_path);

	load_texture(game, &game->wall[S], game->scene->s_path);
	printf("[DEBUG] textura South carregada: %s\n", game->scene->s_path);

	load_texture(game, &game->wall[E], game->scene->e_path);
	printf("[DEBUG] textura East carregada: %s\n", game->scene->e_path);

	load_texture(game, &game->wall[W], game->scene->w_path);
	printf("[DEBUG] textura West carregada: %s\n", game->scene->w_path);
}

static void	load_texture(t_game *game, t_img *img, char *path)
{
	printf("[DEBUG] a carregar textura: %s\n", path);
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->mlx_img)
	{
		perror("[DEBUG] mlx_xpm_file_to_image");
		ft_end(16, NULL);
	}
	img->addr = mlx_get_data_addr(img->mlx_img,
			&img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
	{
		perror("[DEBUG] mlx_get_data_addr");
		ft_end(16, NULL);
	}
}
