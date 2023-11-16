/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:27:19 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 13:12:36 by paulorod         ###   ########.fr       */
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

void	free_textures(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->textures->north->img);
	mlx_destroy_image(cub->mlx, cub->textures->south->img);
	mlx_destroy_image(cub->mlx, cub->textures->west->img);
	mlx_destroy_image(cub->mlx, cub->textures->east->img);
	mlx_destroy_image(cub->mlx, cub->textures->door->img);
	mlx_destroy_image(cub->mlx, cub->textures->animated_wall[0]->img);
	mlx_destroy_image(cub->mlx, cub->minimap->img);
	mlx_destroy_image(cub->mlx, cub->frame_buffer->img);
	free(cub->textures->north);
	free(cub->textures->south);
	free(cub->textures->west);
	free(cub->textures->east);
	free(cub->textures->door);
	free(cub->textures->animated_wall[0]);
	free(cub->textures);
	free(cub->minimap);
	free(cub->frame_buffer);
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
	free_colors(cub);
	free_textures(cub);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub);
	exit(0);
}
