/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:19:41 by pmachado          #+#    #+#             */
/*   Updated: 2025/06/02 21:36:52 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		check_scene(char *path, t_scene *scene);
void		read_scene(char *path, t_scene *scene);
void		check_for_empty(t_scene *scene);
void		separate_map(t_scene *scene);

int			get_map_start_index(char **lines);
int			count_map_lines(char **lines);
void		copy_map_lines(t_scene *scene, int start, int count);
int			ft_get_max_line_length(char **map);
bool		ft_is_map_line(char *line);
int			ft_count_lines(char *path);

int	get_map_start_index(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (ft_is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	count_map_lines(char **lines)
{
	int	count;

	count = 0;
	while (lines[count])
		count++;
	return (count);
}

void	copy_map_lines(t_scene *scene, int start, int count)
{
	int	i;

	scene->map = ft_calloc(count + 1, sizeof(char *));
	if (!scene->map)
		ft_end(ERROR_MALLOC, scene);
	i = 0;
	while (i < count)
	{
		scene->map[i] = ft_strdup(scene->raw_lines[start + i]);
		if (!scene->map[i])
			ft_end(ERROR_MALLOC, scene);
		i++;
	}
	scene->map[i] = NULL;
}

int	ft_get_max_line_length(char **map)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

bool	ft_is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0' || *line == 'N'
		|| *line == 'S' || *line == 'E' || *line == 'W');
}

int	ft_count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_end(ERROR_FD, NULL);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		free(line);
		count++;
	}
	close(fd);
	return (count);
}