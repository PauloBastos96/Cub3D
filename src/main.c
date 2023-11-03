/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:26 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/03 17:19:37 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/// Initialize the game
/// @param cub The cub struct
void	game_init(t_cub *cub)
{
	cub->show_fps = false;
	cub->player = ft_calloc(sizeof(t_player), 1);
	cub->minimap = ft_calloc(sizeof(t_image), 1);
	if (!cub->player)
		throw_err("Couldn't create player struct", cub);
	mlx_setup(cub);
	register_hooks(cub);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		throw_err("Invalid arguments", NULL);
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		throw_err("Couldn't create cub struct", cub);
	game_init(cub);
	if (check_file_ext(av[1]))
		return (0);
	read_map(cub, av[1]);
	cub->minimap = create_new_image(cub->mlx,
			cub->width * 10, cub->height * 10);
	mlx_loop(cub->mlx);
	exit_game(cub);
	return (0);
}
