/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:26 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/24 13:21:55 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof(t_cub));
	if (ac != 2)
		throw_err("Invalid arguments", cub);
	if (check_file_ext(av[1]))
		return (0);
	read_map(cub, av[1]);
	exit_game(cub);
	return (0);
}
