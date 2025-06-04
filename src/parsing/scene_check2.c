/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:53:41 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/04 18:10:04 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_elements(t_scene *scene)
{
	int	i;

	i = 0;
	while (scene->raw_lines[i] && !ft_is_map_line(scene->raw_lines[i])) //enquanto nao for o inicio do mapa
	{
		if (scene->raw_lines[i][0] != '\0')
			parse_textures(scene, scene->raw_lines[i]); //retirar texturas e cores
		i++;
	}
	if (!scene->n_path || !scene->s_path || !scene->e_path || !scene->w_path
		|| scene->floor_color == -1 || scene->sky_color == -1)
		ft_end(9, scene); //estes campos devem vir populados
}
