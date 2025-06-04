/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:23 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/04 17:33:55 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_textures(t_scene *scene, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_NO(scene, line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_SO(scene, line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_WE(scene, line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_EA(scene, line);
	else
		parse_colors(scene, line);
}

void	parse_NO(t_scene *scene, char *line)
{
	if (scene->n_path)
		ft_end(10, scene);
	scene->n_path = ft_strtrim(line + 3, " \t"); //skipa "NO " e copia "./textures/wall.xpm"
}
void	parse_SO(t_scene *scene, char *line)
{
	if (scene->s_path)
		ft_end(10, scene);
	scene->s_path = ft_strtrim(line + 3, " \t"); //skipa "SO " e copia "./textures/wall.xpm"
}
void	parse_WE(t_scene *scene, char *line)
{
	if (scene->w_path)
		ft_end(10, scene);
	scene->w_path = ft_strtrim(line + 3, " \t"); //skipa "WE " e copia "./textures/wall.xpm"
}
void	parse_EA(t_scene *scene, char *line)
{
	if (scene->e_path)
		ft_end(10, scene);
	scene->e_path = ft_strtrim(line + 3, " \t"); //skipa "EA " e copia "./textures/wall.xpm"
}