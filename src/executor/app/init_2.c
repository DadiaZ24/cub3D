/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:12:27 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/12 21:13:34 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
