/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:34:18 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/21 14:33:05 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**get_trimmed_rgb(char **colors);

void	parse_colors(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->scene->floor_color != -1)
			ft_end(10, game);
		game->scene->floor_color = parse_rgb(line + 2);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->scene->sky_color != -1)
			ft_end(10, game);
		game->scene->sky_color = parse_rgb(line + 2);
	}
	else
		ft_end(15, game);
}

int	parse_rgb(const char *line)
{
	char	**colors;
	char	**trimmed;
	int		r;
	int		g;
	int		b;

	colors = ft_split(line, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		rgb_error(colors);
	trimmed = get_trimmed_rgb(colors);
	if (!trimmed)
		rgb_error(colors);
	free_array(colors, 3);
	r = ft_atoi(trimmed[0]);
	g = ft_atoi(trimmed[1]);
	b = ft_atoi(trimmed[2]);
	free_array(trimmed, 3);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_end(15, NULL);
	return (r * 65536 + g * 256 + b);
}

static char	**get_trimmed_rgb(char **colors)
{
	char	**trimmed;

	trimmed = malloc(sizeof(char *) * 3);
	if (!trimmed)
		rgb_error(colors);
	trimmed[0] = trim_and_check_digit(colors[0]);
	trimmed[1] = trim_and_check_digit(colors[1]);
	trimmed[2] = trim_and_check_digit(colors[2]);
	if (!trimmed[0] || !trimmed[1] || !trimmed[2])
		rgb_error(colors);
	return (trimmed);
}

char	*trim_and_check_digit(char *str)
{
	char	*trimmed;

	trimmed = ft_strtrim(str, " \t");
	if (!trimmed)
		return (NULL);
	if (!ft_isdigit_str(trimmed))
	{
		free(trimmed);
		return (NULL);
	}
	return (trimmed);
}

bool	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
