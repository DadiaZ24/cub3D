/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:13:55 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/27 12:17:19 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool arg_parse(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (printf("%s%s\n", ERROR, ERROR_ARGC), false);
	return (true);
}

int	main(int ac, char **av)
{
	

	if (!arg_parse(ac, av))
		return (-1);
	
	return (0);
}

