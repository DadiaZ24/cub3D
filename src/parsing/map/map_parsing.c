/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:41:10 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/03/25 11:10:59 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool map_char_parser(char *path)
{
	char	**file;
	int		i;

	file = ft_split(path, '/');
	if (!file)
		return (printf("erroooooooo"), false);
	i = 0;
	while (file[i])
		i++;
	if ((!ft_strrchr(file[i - 1], '.')) ||
		(ft_strncmp(ft_strrchr(file[i - 1], '.'), FILE_EXTENSION, 5)))
		return (printf("Error: Extension is not '.cub'.\n"), false);
	if (ft_strlen(file[i - 1]) <= 4)
		return (printf("Error: No file name, just extension.\n"), false);
	free_array(file);
	return (true);
}

void	init_map_parser(char *path)
{
	//t_map_parser mparser;
	int fd;

	//(void)mparser;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("%s", path);
		exit(-1);
	}

/* 	while (av)
	{
		
	} */
}

bool is_valid_char(char position)
{
	return (position == ZERO || position == ONE || position == NORTH
		|| position == SOUTH || position == EAST || position == WEST);
}
