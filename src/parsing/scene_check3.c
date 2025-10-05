/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:56:01 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/05 13:56:01 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	separate_map(t_scene *scene)
{
	int	start;
	int	count;

	start = get_map_start_index(scene->raw_lines);
	if (start == -1)
		ft_end(8, NULL);
	count = count_map_lines(scene->raw_lines + start);
	scene->map_size.y = count;
	copy_map_lines(scene, start, count);
	scene->map_size.x = ft_get_max_line_length(scene->map);
}

void	check_for_empty(t_scene *scene)
{
	if (!scene->raw_lines || !scene->raw_lines[0])
		ft_end(12, NULL);
}
