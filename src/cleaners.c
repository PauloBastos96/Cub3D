/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:27:19 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/24 12:46:46 by paulorod         ###   ########.fr       */
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

/// Free the map
/// @param cub Cub struct
void	free_map(t_cub *cub)
{
	int	i;

	i = 0;
	if (!cub->map)
		return ;
	while (cub->map[i])
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
}

/// Free the textures and colors
/// @param cub Cub struct
void	free_colors(t_cub *cub)
{
	free(cub->floor_color);
	free(cub->ceiling_color);
}

/// Clean the game and exit
/// @param cub 
void	exit_game(t_cub *cub)
{
	free_split(cub->file);
	free_map(cub);
	free_colors(cub);
	free(cub);
	exit(0);
}
