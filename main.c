/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:13:55 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/03/25 14:44:29 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char *av)
{
	char	*line;
	int		rows;
	int		fd;
	
	rows = 0;
	if ((fd = open(av, O_RDONLY)) <= 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (line)
		free(line);
		line = get_next_line(fd);
		rows++;
	}
	if (line)
	free(line);
	close(fd);
	return (rows);
}

t_data	*init(char *av, t_data *data)
{
	char	**map_file;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	line = NULL;
	map_file = NULL;
	data->rows = count_lines(av);
	fd = 0;
	if ((fd = open(av, O_RDONLY)) <= 0)
		return (NULL);
	map_file = malloc(sizeof(char *) * (data->rows + 1));
	if (!map_file)
		return (NULL);
	map_file[data->rows] = NULL;
	line = get_next_line(fd);
	while (line)
	{
		map_file[i++] = line;
		line = get_next_line(fd);
	}
	i = 0;
	//set_data(&data, map_file);
	close(fd);
	return (data);
}

/* t_data	**set_data(t_data **data, char *map_file)
{

} */

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;

	// TODO: DELETE WHEN WE HAVE THE SKY AND FLOOR PARSING COLORS
	data.sky_color = 0x87CEEB;
	data.floor_color = 0x654321;
	if (ac != 2)
		return (printf("%s%s\n", ERROR, ERROR_ARGC), 1);
	init(av[1], &data);
	//map_char_parser(av[1]);
	if (!executor(&game, &data))
		return (printf("%s%s\n", ERROR, "Error executing game."), 1);
	printf("Sai bem\n");
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