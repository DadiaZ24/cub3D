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

static bool all_elements_found(t_scene *scene);

void check_scene(char *path, t_scene *scene)
{
	read_scene(path, scene); // ler o ficheiro .cub e copiar as linhas para scene->raw_lines
	check_for_empty(scene);	 // verificar se esta vazio

	validate_elements(scene); // all metadata filled?

	printf("[DEBUG] Elementos validos. Checkar mapa agora.\n");

	separate_map(scene); // extract map
	for (int j = 0; scene->map[j]; j++)
		printf("[MAP] %s\n", scene->map[j]);
	validate_map_characters(scene->map); // only valid characters

	printf("[DEBUG] Caracteres no mapa validos.\n");

	validate_map(scene); // check closure, player
}

void read_scene(char *path, t_scene *scene)
{
	int fd;
	int line_count;
	int i;
	char *line;
	char *clean;
	char *clean2;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_end(4, NULL);
	line_count = ft_count_lines(path);
	scene->raw_lines = ft_calloc(line_count + 1, sizeof(char *)); // copia das linhas do ficheiro
	if (!scene->raw_lines)
		ft_end(3, NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		clean = spaces_for_tabs(line);					// substituir tabs por espacos
		clean2 = ft_strtrim(clean, "\n");				// remove \n do final da linha
		scene->raw_lines[i] = ft_strtrim(clean2, "\r"); // remove \r do final da linha
		if (clean != line)
			free(clean);
		if (clean2 != line)
			free(clean2);
		free(line);
		if (!scene->raw_lines[i])
			ft_end(3, NULL);
		i++;
	}
	scene->raw_lines[i] = NULL;
	close(fd);
}

void check_for_empty(t_scene *scene)
{
	if (!scene->raw_lines || !scene->raw_lines[0])
		ft_end(12, NULL);
}

void separate_map(t_scene *scene)
{
	int start;
	int count;

	start = get_map_start_index(scene->raw_lines); // verifica onde começa o mapa
	if (start == -1)
		ft_end(8, NULL);
	count = count_map_lines(scene->raw_lines + start); // conta as linhas do mapa excluindo a metadata com info das texturas e cores
	scene->map_size.y = count;						   // define a altura do mapa
	copy_map_lines(scene, start, count);			   // copia as linhas do mapa para scene->map
	scene->map_size.x = ft_get_max_line_length(scene->map);
}

void validate_elements(t_scene *scene)
{
	int i;
	char *trimmed;

	i = 0;
	while (scene->raw_lines[i])
	{
		trimmed = ft_strtrim(scene->raw_lines[i], " \t");
		if (trimmed[0] != '\0')
		{
			if (ft_is_map_line(trimmed) && all_elements_found(scene))
			{
				free(trimmed);
				break;
			}
			parse_textures(scene, trimmed);
		}
		free(trimmed);
		i++;
	}
	printf("[DEBUG] n_path: %s\n", scene->n_path);
	printf("[DEBUG] s_path: %s\n", scene->s_path);
	printf("[DEBUG] w_path: %s\n", scene->w_path);
	printf("[DEBUG] e_path: %s\n", scene->e_path);
	printf("[DEBUG] floor_color: %d\n", scene->floor_color);
	printf("[DEBUG] sky_color: %d\n", scene->sky_color);
	printf("[DEBUG] Texturas e cores gravadas na struct.\n");
	if (!scene->n_path || !scene->s_path || !scene->e_path || !scene->w_path || scene->floor_color == -1 || scene->sky_color == -1)
		ft_end(9, NULL); // estes campos devem vir populados
}

static bool all_elements_found(t_scene *scene)
{
	return (scene->n_path && scene->s_path && scene->e_path && scene->w_path && scene->floor_color != -1 && scene->sky_color != -1);
}
