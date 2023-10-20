/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:26 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/20 16:17:20 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map(t_cub cub)
{
	int	i;

	i = 0;
	while (cub.map[i])
	{
		free(cub.map[i]);
		i++;
	}
	free(cub.map);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		return (printf("Too many arguments\n"), 0);
	if (check_file_ext(av[1]))
		return (0);
	read_map(&cub, av[1]);
	free_split(cub.file);
	free_map(cub);
	return (0);
}
