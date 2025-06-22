/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:53:41 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/07 20:52:47 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map_characters(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			printf("[DEBUG] TESTE TESTE.\n");
			if (!is_valid_map_char(map[y][x]))
			{
				printf("[DEBUG] Caractere invalido: %c na posicao (%d, %d)\n", map[y][x], x, y);	
				ft_end(7, NULL);
			}
			x++;
		}
		y++;
	}
}

void	validate_map(t_scene *scene)
{
	pad_map(scene);				//tornar o mapa retangular
	find_player(scene);			//gravar posicao do player e direcao
	check_closed_map(scene);	//floodfill e ver se o mapa esta fechado
}

void	pad_map(t_scene *scene)
{
	int		y;
	int		len;
	char	*new_line;

	y = 0;
	while (scene->map[y])
	{
		len = ft_strlen(scene->map[y]); //len da linha atual
		if (len < scene->map_size.x) //se len for menor do que a maior linha do mapa
		{
			new_line = ft_calloc(scene->map_size.x + 1, sizeof(char)); //alocar memoria para a nova linha
			if (!new_line)
				ft_end(3, NULL);
			ft_memset(new_line, ' ', scene->map_size.x); //preenche a string com espaços
			ft_memcpy(new_line, scene->map[y], len); //copia a linha atual para a nova linha
			free(scene->map[y]); //liberta a linha antiga
			scene->map[y] = new_line; //substitui a linha antiga pela nova
		}
		y++;
	}
}

void	find_player(t_scene *scene)
{
	int		y;
	int		x;
	bool	found;

	found = false;
	y = 0;
	while (scene->map[y])
	{
		x = 0;
		while (scene->map[y][x])
		{
			if (ft_strchr("NSEW", scene->map[y][x]))
			{
				if (found)
					ft_end(10, NULL);
				set_spawn(scene, x, y, scene->map[y][x]);
				scene->map[y][x] = '0'; //substitui a posicao do player por '0'
				found = true;
			}
			x++;
		}
		y++;
	}
	if (!found)
		ft_end(14, NULL);
}

void	check_closed_map(t_scene *scene)
{
	char	**copy;
	int		x;
	int		y;

	x = scene->spawn.x;
	y = scene->spawn.y;
	copy = duplicate_map(scene);
	flood_fill(copy, scene->map_size.x, scene->map_size.y, x, y);
	free_array(copy, scene->map_size.y);
}
