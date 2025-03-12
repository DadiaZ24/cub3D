/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:13:55 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/03/11 15:07:57 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	**init(char *av)
{
	t_data	**data;
	char	*map_file;
	int		fd;

	data = NULL;
	map_file = NULL;
	fd = 0;
	if ((fd = open(av, O_RDONLY)) <= 0)
		return (NULL);
	map_file = get_next_line(fd);
	if (!map_file)
		return (NULL);
	/* data = set_data(data, map_file); */
	
	close(fd);
	return (data);
}

/* t_data	**set_data(t_data **data, char *map_file)
{

} */

int	main(int ac, char **av)
{
	t_data	**data;

	data = NULL;
	if (ac != 2)
		return (printf("%s%s\n", ERROR, ERROR_ARGC), 1);
	data = init(av[1]);
	if (!data)
		return (printf("%s%s\n", ERROR, "Error fetching map data."), 1);
	//map_char_parser(av[1]);
	return (0);
}


/* To-do:

- import map and config into data structure:
	- read from file;
	- set each information onto data structure;
- Map validation:
	- Check if all the characters are 0, 1, N, S, E, W
	- Check if the map is all closed with walls (1)
	
	
	*/