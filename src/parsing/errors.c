/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:23:43 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/04 23:20:43 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_end(int nbr, t_game *g)
{
	if (nbr == 1)
		printf("%s\n", ERROR_NBR_ARGS);
	else if (nbr == 2)
		printf("%s\n", ERROR_INVALID_EXTENSION);
	else if (nbr == 3)
		printf("%s\n", ERROR_MALLOC);
	else if (nbr == 4)
		printf("%s\n", ERROR_FD);
	else if (nbr == 5)
		printf("%s\n", ERROR_MLX_INIT);
	else if (nbr == 6)
		printf("%s\n", ERROR_MAP_PROCESSING);
	else if (nbr == 7)
		printf("%s\n", ERROR_MAP_INVALID);
	else if (nbr == 8)
		printf("%s\n", ERROR_MAP_PATH);
	else if (nbr == 9)
		printf("%s\n", ERROR_MISS_ELEMTS);
	else if (nbr == 10)
		printf("%s\n", ERROR_DUPLICATE_ELEMENT);
	else if (nbr == 11)
		printf("%s\n", ERROR_UNKNOWN_ELEMENT);
	else if (nbr == 12)
		printf("%s\n", ERROR_EMPTY_FILE);
	else if (nbr == 13)
		printf("%s\n", ERROR_MAP_NOT_CLOSED);
	else if (nbr == 14)
		printf("%s\n", ERROR_PLAYER_NOT_FOUND);
	else if (nbr == 15)
		printf("%s\n", ERROR_INVALID_COLOR);
	if (nbr != 2 && nbr != 1)
		free_all(g);
	exit(1);
}

//* *******************************-Para acertar ainda-********************************************/
 
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

void	free_array(char **arr, int max)
{
	int i = 0;

	if (!arr)
		return ;
	while (i < max && arr[i])
		free(arr[i++]);
	free(arr);
}

int	ft_exit(t_game *g)
{
	free_all(g);
	exit(EXIT_SUCCESS);
}
