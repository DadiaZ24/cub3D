/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:41:10 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/06/04 13:41:49 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_validate_args(int ac, char **av)
{
	if (ac != 2)
		ft_end(1, NULL);
	if (ft_strlen(av[1]) < 4
		|| ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)// verifica se o ficheiro tem a extensao .cub
		ft_end(2, NULL);
	return (true);
}
