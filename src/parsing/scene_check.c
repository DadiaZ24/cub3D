/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:40:15 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/04 23:02:09 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_scene(char *path, t_scene *scene)
{
	read_scene(path, scene);					// ler o ficheiro .cub e copiar as linhas para scene->raw_lines
	check_for_empty(scene);						// verificar se esta vazio
	separate_map(scene);						// extract map
	validate_elements(scene);					// all metadata filled?
	validate_map_characters(scene->map);		// only valid characters
	validate_map(scene);						// check closure, player
}

void	read_scene(char *path, t_scene *scene)
{
	int		fd;
	int		line_count;
	int		i;
	char	*line;
	char	*clean;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_end(4, scene);
	line_count = ft_count_lines(path);
	scene->raw_lines = ft_calloc(line_count + 1, sizeof(char *)); //copia das linhas do ficheiro
	if (!scene->raw_lines)
		ft_end(ERROR_MALLOC, scene);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		clean = spaces_for_tabs(line); //substituir tabs por espacos
		scene->raw_lines[i] = ft_strtrim(clean, "\n"); //remove \n do final da linha
		free(clean);
		free(line);
		if (!scene->raw_lines[i])
			ft_end(ERROR_MALLOC, scene);
		i++;
	}
	scene->raw_lines[i] = NULL;
	close(fd);
}

void	check_for_empty(t_scene *scene)
{
	if (!scene->raw_lines || !scene->raw_lines[0])
		ft_end(ERROR_EMPTY_FILE, scene);
}

void	separate_map(t_scene *scene)
{
	int	start;
	int	count;

	start = get_map_start_index(scene->raw_lines); // verifica onde começa o mapa
	if (start == -1)
		ft_end(8, scene);
	count = count_map_lines(scene->raw_lines + start); // conta as linhas do mapa excluindo a metadata com info das texturas e cores
	scene->map_size.y = count; //define a altura do mapa
	copy_map_lines(scene, start, count); // copia as linhas do mapa para scene->map
	scene->map_size.x = ft_get_max_line_length(scene->map);
}

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