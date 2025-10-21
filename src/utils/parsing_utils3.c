/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:52:23 by pmachado          #+#    #+#             */
/*   Updated: 2025/10/21 14:34:15 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_textures(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_no(game, line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_so(game, line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_we(game, line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_ea(game, line);
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		parse_colors(game, line);
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		parse_colors(game, line);
	else
		ft_end(11, game);
}

void	parse_no(t_game *game, char *line)
{
	if (game->scene->n_path)
		ft_end(10, game);
	game->scene->n_path = ft_strtrim(line + 3, " \t");
	if (!game->scene->n_path)
		ft_end(3, game);
	if (!validate_texture_path(game->scene->n_path))
	{
		free(line);
		ft_end(17, game);
	}
}

void	parse_so(t_game *game, char *line)
{
	if (game->scene->s_path)
		ft_end(10, game);
	game->scene->s_path = ft_strtrim(line + 3, " \t");
	if (!game->scene->s_path)
		ft_end(3, game);
	if (!validate_texture_path(game->scene->s_path))
	{
		free(line);
		ft_end(17, game);
	}
}

void	parse_we(t_game *game, char *line)
{
	if (game->scene->w_path)
		ft_end(10, game);
	game->scene->w_path = ft_strtrim(line + 3, " \t");
	if (!game->scene->w_path)
		ft_end(3, game);
	if (!validate_texture_path(game->scene->w_path))
	{
		free(line);
		ft_end(17, game);
	}
}

void	parse_ea(t_game *game, char *line)
{
	if (game->scene->e_path)
		ft_end(10, game);
	game->scene->e_path = ft_strtrim(line + 3, " \t");
	if (!game->scene->e_path)
		ft_end(3, game);
	if (!validate_texture_path(game->scene->e_path))
	{
		free(line);
		ft_end(17, game);
	}
}
