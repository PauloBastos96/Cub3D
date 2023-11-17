/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:26 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/17 14:20:16 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/// Initialize the game
/// @param cub The cub struct
void	game_init(t_cub *cub)
{
	cub->show_debug_line = false;
	cub->show_minimap = false;
	cub->show_fps = false;
	cub->show_fog = false;
	cub->debug_line = 0;
	cub->prop_x = 0;
	cub->prop_y = 0;
	cub->textures = ft_calloc(sizeof(t_textures), 1);
	cub->player = ft_calloc(sizeof(t_player), 1);
	if (!cub->player || !cub->textures)
		throw_err("Couldn't allocate memory", cub);
	cub->textures->anim_wall_paths = ft_split(ANIM_WALLS, ' ');
	cub->textures->door_path = DOOR_TEXTURE;
	cub->player->position = ft_calloc(sizeof(t_vector), 1);
	cub->player->direction = ft_calloc(sizeof(t_vector), 1);
	if (!cub->player->position || !cub->player->direction
		|| !cub->textures->anim_wall_paths)
		throw_err("Couldn't allocate memory", cub);
	mlx_setup(cub);
	register_hooks(cub);
}

/// Create a new t_image from a xpm file
/// @param cub The cub struct
/// @param path The path to the xpm file
/// @return A new t_image
t_image	*create_xpm_images(t_cub *cub, char *path)
{
	t_image	*image;

	image = ft_calloc(sizeof(t_image), 1);
	if (!image)
		throw_err("Couldn't allocate memory", cub);
	image->img = mlx_xpm_file_to_image(cub->mlx, path, &image->w, &image->h);
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_len, &image->endian);
	return (image);
}

/// Creates the game textures
/// @param cub The cub struct
void	creates_textures(t_cub *cub)
{
	int	i;

	i = 0;
	cub->minimap = create_new_image(cub->mlx, cub->width * MINIMAP_SCALE,
			cub->height * MINIMAP_SCALE);
	cub->textures->north = create_xpm_images(cub, cub->textures->north_path);
	cub->textures->south = create_xpm_images(cub, cub->textures->south_path);
	cub->textures->west = create_xpm_images(cub, cub->textures->west_path);
	cub->textures->east = create_xpm_images(cub, cub->textures->east_path);
	cub->textures->door = create_xpm_images(cub, cub->textures->door_path);
	while (i < 4)
	{
		cub->textures->animated_walls[i] = create_xpm_images(cub,
				cub->textures->anim_wall_paths[i]);
		i++;
	}
	if (!cub->minimap || !cub->textures->north || !cub->textures->south
		|| !cub->textures->west || !cub->textures->east
		|| !cub->textures->door || !cub->textures->animated_walls[0]
		|| !cub->textures->animated_walls[1]
		|| !cub->textures->animated_walls[2]
		|| !cub->textures->animated_walls[3])
		throw_err("Couldn't create textures", cub);
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
