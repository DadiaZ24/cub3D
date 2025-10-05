/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:19:41 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/05 15:40:46 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//----------read_scene-------------//

int	ft_count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_end(4, NULL);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	*spaces_for_tabs(char *line)
{
	int		tabs;
	int		size;
	char	*new_line;

	tabs = has_tabs(line);
	if (!tabs)
		return (line);
	size = ft_strlen(line);
	new_line = ft_calloc((size - tabs) + (tabs * 4) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	change_tabs(line, new_line);
	free(line);
	return (new_line);
}

int	has_tabs(const char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == '\t')
			count++;
		line++;
	}
	return (count);
}

void	change_tabs(const char *line, char *new_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
}
