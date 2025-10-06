/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:23 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/05 18:13:55 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_textures(t_scene *scene, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_no(scene, line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_so(scene, line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_we(scene, line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_ea(scene, line);
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		parse_colors(scene, line);
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		parse_colors(scene, line);
	else
		ft_end(11, NULL);
}

void	parse_no(t_scene *scene, char *line)
{
	if (scene->n_path)
		ft_end(10, NULL);
	scene->n_path = ft_strtrim(line + 3, " \t");
}

void	parse_so(t_scene *scene, char *line)
{
	if (scene->s_path)
		ft_end(10, NULL);
	scene->s_path = ft_strtrim(line + 3, " \t");
}

void	parse_we(t_scene *scene, char *line)
{
	if (scene->w_path)
		ft_end(10, NULL);
	scene->w_path = ft_strtrim(line + 3, " \t");
}

void	parse_ea(t_scene *scene, char *line)
{
	if (scene->e_path)
		ft_end(10, NULL);
	scene->e_path = ft_strtrim(line + 3, " \t");
}
