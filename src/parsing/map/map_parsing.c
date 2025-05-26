/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:41:10 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/05/26 20:40:27 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_validate_args(int ac, char **av)
{
	if (ac != 2)
		ft_end(1, NULL);
	if (ft_strlen(av[1]) < 4
		|| ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		ft_end(2, NULL);
	return (true);

	//ERROR_FILE_EXTENSION
}

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
