/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:13:55 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/21 14:27:46 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (!ft_validate_args(ac, av))
	{
		printf("%s\n", ERROR_INVALID_ARGS);
		exit(1);
	}
	game = ft_init_game(av[1]);
	if (!game)
	{
		printf("Failed to initialize game\n");
		exit(1);
	}
	init_game_data(game);
	mlx_loop(game->mlx);
	return (0);
}
