/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:23:43 by pmachado          #+#    #+#             */
/*   Updated: 2025/05/26 20:29:01 by pmachado         ###   ########.fr       */
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
		printf("%s\n", ERROR_MAP_RECT);
	else if (nbr == 8)
		printf("%s\n", ERROR_MAP_INVALID);
	else if (nbr == 9)
		printf("%s\n", ERROR_MAP_PATH);
	if (nbr != 2 && nbr != 1)
		free_all(g);
	exit(1);
}

//* *******************************-Para acertar ainda-********************************************/

/* 
void	free_all(t_game *g)
{
	if (!g)
		return ;
	if (g->world_map)
		free_map(g->world_map);
	if (g->art_asset.canvas)
		mlx_destroy_image(g->pixel_magic, g->art_asset.canvas);
	if (g->view_portal)
		mlx_destroy_window(g->pixel_magic, g->view_portal);
	if (g->pixel_magic)
	{
		mlx_destroy_display(g->pixel_magic);
		free(g->pixel_magic);
	}
	free(g);
}

void	free_map(t_map *world_map)
{
	int	i;

	if (!world_map || !world_map->layout)
		return ;
	i = 0;
	while (world_map->layout[i])
	{
		free(world_map->layout[i]);
		i++;
	}
	free(world_map->layout);
	free(world_map);
}

void	free_array(char **array, int row)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < row)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_exit(t_game *g)
{
	free_all(g);
	exit(EXIT_SUCCESS);
}
 */