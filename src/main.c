/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:26 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/25 16:27:07 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/// Initialize the game
/// @param cub The cub struct
void	game_init(t_cub *cub)
{
	cub->last_frame = 0;
	cub->player = ft_calloc(sizeof(t_player), 1);
	if (!cub->player)
		throw_err("Couldn't create player struct", cub);
	mlx_setup(cub);
	register_hooks(cub);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		throw_err("Couldn't create cub struct", cub);
	if (ac != 2)
		throw_err("Invalid arguments", cub);
	game_init(cub);
	if (check_file_ext(av[1]))
		return (0);
	read_map(cub, av[1]);
	mlx_loop(cub->mlx);
	exit_game(cub);
	return (0);
}
