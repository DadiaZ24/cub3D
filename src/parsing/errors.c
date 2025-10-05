/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:23:43 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/05 18:05:55 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*print_error_msg(int nbr)
{
	static char	*messages[16];
	int			i;

	i = 0;
	messages[i++] = "Invalid number of arguments";
	messages[i++] = "Invalid file extension";
	messages[i++] = "Malloc failed";
	messages[i++] = "File descriptor error";
	messages[i++] = "MLX initialization failed";
	messages[i++] = "Map processing error";
	messages[i++] = "Map invalid";
	messages[i++] = "Map path error";
	messages[i++] = "Missing elements";
	messages[i++] = "Duplicate element";
	messages[i++] = "Unknown element";
	messages[i++] = "Empty file";
	messages[i++] = "Map not closed";
	messages[i++] = "Player not found";
	messages[i++] = "Invalid color";
	messages[i++] = "Failed to load texture";
	if (nbr < 1 || nbr > 16)
		return ("Unknown error");
	return (messages[nbr - 1]);
}

void	ft_end(int nbr, t_game *g)
{
	printf("Error\n%s\n", print_error_msg(nbr));
	if (nbr != 1 && nbr != 2)
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
	if (g->game_img.mlx_img && g->mlx)
		mlx_destroy_image(g->mlx, g->game_img.mlx_img);
	i = 0;
	while (i < 4)
	{
		if (g->wall[i].mlx_img && g->mlx)
			mlx_destroy_image(g->mlx, g->wall[i].mlx_img);
		i++;
	}
	if (g->window && g->mlx)
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

void	free_array(char **arr, int max)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < max && arr[i])
		free(arr[i++]);
}
