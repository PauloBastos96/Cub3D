/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:26 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/10 13:44:50 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/// Initialize the game
/// @param cub The cub struct
void	game_init(t_cub *cub)
{
	cub->show_fps = false;
	cub->show_minimap = false;
	cub->debug_line = 0;
	cub->textures = ft_calloc(sizeof(t_textures), 1);
	cub->player = ft_calloc(sizeof(t_player), 1);
	cub->player->position = ft_calloc(sizeof(t_vector), 1);
	cub->player->direction = ft_calloc(sizeof(t_vector), 1);
	cub->minimap = ft_calloc(sizeof(t_image), 1);
	if (!cub->player)
		throw_err("Couldn't create player struct", cub);
	mlx_setup(cub);
	register_hooks(cub);
}

t_image	*create_xpm_images(t_cub *cub, char *path)
{
	t_image	*image;

	image = ft_calloc(sizeof(t_image), 1);
	image->img = mlx_xpm_file_to_image(cub->mlx, path, &image->w, &image->h);
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_len, &image->endian);
	return (image);
}

void	creates_textures(t_cub *cub)
{
	cub->minimap = create_new_image(cub->mlx, cub->width * MINIMAP_SCALE, 
			cub->height * MINIMAP_SCALE);
	cub->textures->north = create_xpm_images(cub, cub->textures->north_path);
	cub->textures->south = create_xpm_images(cub, cub->textures->south_path);
	cub->textures->west = create_xpm_images(cub, cub->textures->west_path);
	cub->textures->east = create_xpm_images(cub, cub->textures->east_path);
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
	creates_textures(cub);
	mlx_loop(cub->mlx);
	exit_game(cub);
	return (0);
}
