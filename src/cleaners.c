/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:27:19 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 14:48:51 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/// Free a split array
/// @param split Split array
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

/// Free the textures and colors
/// @param cub Cub struct
void	free_colors(t_cub *cub)
{
	free(cub->floor_color);
	free(cub->ceiling_color);
}

/// Free a texture
/// @param cub The cub struct
/// @param texture The texture to free
void	free_texture(t_cub *cub, t_image *texture)
{
	if (!texture)
		return ;
	mlx_destroy_image(cub->mlx, texture->img);
	free(texture);
}

/// Free all game textures
/// @param cub The cub struct
void	free_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
		free_texture(cub, cub->textures->animated_walls[i++]);
	free_texture(cub, cub->textures->north);
	free_texture(cub, cub->textures->south);
	free_texture(cub, cub->textures->west);
	free_texture(cub, cub->textures->east);
	free_texture(cub, cub->textures->door);
	free_texture(cub, cub->minimap);
	free_texture(cub, cub->frame_buffer);
	free(cub->textures);
}

/// Clean the game and exit
/// @details The textures are freed along with cub->file
/// @param cub The cub struct
void	exit_game(t_cub *cub)
{
	free_split(cub->file);
	free_split(cub->map);
	free(cub->player->position);
	free(cub->player->direction);
	free(cub->player);
	free_split(cub->textures->anim_wall_paths);
	free_colors(cub);
	free_textures(cub);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub);
	exit(0);
}
