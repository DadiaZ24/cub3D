/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:03:34 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/16 15:41:56 by pmachado         ###   ########.fr       */
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
