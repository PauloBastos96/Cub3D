/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:54:42 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/25 14:55:55 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Set player direction
/// @param player The player struct
/// @param dir The direction character
void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
}

/// Check if player exists in map file
/// @param line The map line to check
/// @param counter Player character counter
void	check_player(char *line, int *counter)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("NSWE", line[i]))
			(*counter)++;
		i++;
	}
}
