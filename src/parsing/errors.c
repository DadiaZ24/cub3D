/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:23:43 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/16 14:10:19 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*print_error_msg(int nbr)
{
	static const char	*messages[] = {
		"Invalid number of arguments",
		"Invalid file extension",
		"Malloc failed",
		"File descriptor error",
		"MLX initialization failed",
		"Map processing error",
		"Map invalid",
		"Map path error",
		"Missing elements",
		"Duplicate element",
		"Unknown element",
		"Empty file",
		"Map not closed",
		"Player not found",
		"Invalid color",
		"Failed to load texture",
		"Invalid path to texture"
	};

	if (nbr < 1 || nbr > 17)
		return ("Unknown error");
	return (messages[nbr - 1]);
}

void	ft_end(int nbr, t_game *g)
{
	printf("Error\n%s\n", print_error_msg(nbr));
	if (g && nbr != 1 && nbr != 2)
		free_all(g);
	exit(1);
}

void	free_all(t_game *g)
{
	int	i;

	if (!g)
		return ;
	if (g->scene)
		free_scene(g->scene);
	if (g->game_img.mlx_img)
		mlx_destroy_image(g->mlx, g->game_img.mlx_img);
	i = 0;
	while (i < 4)
	{
		if (g->wall[i].mlx_img)
			mlx_destroy_image(g->mlx, g->wall[i].mlx_img);
		i++;
	}
	if (g->window)
		mlx_destroy_window(g->mlx, g->window);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free(g);
}

void	free_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	if (scene->map)
	{
		i = 0;
		while (scene->map[i])
			free(scene->map[i++]);
		free(scene->map);
	}
	if (scene->raw_lines)
	{
		i = 0;
		while (scene->raw_lines[i])
			free(scene->raw_lines[i++]);
		free(scene->raw_lines);
	}
	free(scene->n_path);
	free(scene->s_path);
	free(scene->e_path);
	free(scene->w_path);
	free(scene);
}
