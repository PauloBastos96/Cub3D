/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:27:19 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/28 15:42:29 by paulorod         ###   ########.fr       */
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

/// Clean the game and exit
/// @details The textures are freed along with cub->file
/// @param cub The cub struct
void	exit_game(t_cub *cub)
{
	free_split(cub->file);
	free_split(cub->map);
	free(cub->player);
	free_colors(cub);
	mlx_destroy_image(cub->mlx, cub->minimap->img);
	mlx_destroy_image(cub->mlx, cub->frame_buffer->img);
	free(cub->minimap);
	free(cub->frame_buffer);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub);
	exit(0);
}
