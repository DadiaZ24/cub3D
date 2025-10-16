/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:43:31 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/12 21:13:03 by pmachado         ###   ########.fr       */
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
