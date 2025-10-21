/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:03:34 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/21 14:53:03 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **arr, int max)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < max && arr[i])
		free(arr[i++]);
	free(arr);
}

void	rgb_error(char **colors)
{
	free_rgb_parts(colors, NULL);
	ft_end(15, NULL);
}

void	free_rgb_parts(char **colors, char **trimmed)
{
	if (colors)
		free_array(colors, 3);
	if (trimmed)
		free_array(trimmed, 3);
}

int	ft_exit(t_game *g)
{
	free_all(g);
	exit(EXIT_SUCCESS);
}

void	free_duplicate_map(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
