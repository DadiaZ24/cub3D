/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:40:15 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/07 21:11:58 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	all_elements_found(t_scene *scene)
{
	return (scene->n_path && scene->s_path && scene->e_path
		&& scene->w_path && scene->floor_color != -1 && scene->sky_color != -1);
}

void	check_scene(char *path, t_scene *scene)
{
	read_scene(path, scene);
	check_for_empty(scene);
	validate_elements(scene);
	separate_map(scene);
	validate_map(scene);
}

static void	read_scene_while(t_scene *scene, t_read_scene *tmp_scene)
{
	tmp_scene->clean = spaces_for_tabs(tmp_scene->line);
	tmp_scene->clean2 = ft_strtrim(tmp_scene->clean, "\n");
	scene->raw_lines[tmp_scene->i] = ft_strtrim(tmp_scene->clean2, "\r");
	if (tmp_scene->clean != tmp_scene->line)
		free(tmp_scene->clean);
	if (tmp_scene->clean2 != tmp_scene->line)
		free(tmp_scene->clean2);
	free(tmp_scene->line);
	if (!scene->raw_lines[tmp_scene->i])
		ft_end(3, NULL);
	tmp_scene->i++;
}

void	read_scene(char *path, t_scene *scene)
{
	t_read_scene	tmp_scene;

	tmp_scene.fd = open(path, O_RDONLY);
	if (tmp_scene.fd < 0)
		ft_end(4, NULL);
	tmp_scene.line_count = ft_count_lines(path);
	scene->raw_lines = ft_calloc(tmp_scene.line_count + 1, sizeof(char *));
	if (!scene->raw_lines)
		ft_end(3, NULL);
	tmp_scene.i = 0;
	tmp_scene.line = get_next_line(tmp_scene.fd);
	while (tmp_scene.line)
	{
		read_scene_while(scene, &tmp_scene);
		tmp_scene.line = get_next_line(tmp_scene.fd);
	}
	scene->raw_lines[tmp_scene.i] = NULL;
	close(tmp_scene.fd);
}

void	validate_elements(t_scene *scene)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (scene->raw_lines[i])
	{
		trimmed = ft_strtrim(scene->raw_lines[i], " \t");
		if (trimmed[0] != '\0')
		{
			if (ft_is_map_line(trimmed) && all_elements_found(scene))
			{
				free(trimmed);
				break ;
			}
			parse_textures(scene, trimmed);
		}
		free(trimmed);
		i++;
	}
	if (!scene->n_path || !scene->s_path || !scene->e_path || !scene->w_path
		|| scene->floor_color == -1 || scene->sky_color == -1)
		ft_end(9, NULL);
}
