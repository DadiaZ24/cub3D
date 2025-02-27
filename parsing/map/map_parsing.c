/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:41:10 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/27 13:49:32 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool map_char_parser(char *path)
{
	if (!parse_extension(path))
		return (false);


	
	return (true);
	
}

bool	parse_extension(char *path)
{
	if (ft_strncmp(ft_strrchr(path, '.'), FILE_EXTENSION, 4))
		return (false);
	return (true);
}



void	init_map_parser(char *path);
{
	t_map_parser mparser;
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("%s", );
		exit(-1);
	}

	while (av)
	{
		
	}
}

bool is_valid_char(char position)
{
	return (position == ZERO || position == ONE || position == NORTH
		|| position == SOUTH || position == EAST || position == WEST);
}