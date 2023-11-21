/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:54:42 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/17 15:20:08 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/// Set player direction
/// @param player The player struct
/// @param dir The direction character
void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->direction->x = 0;
		player->direction->y = 1;
		player->angle = PI / 2;
	}
	else if (dir == 'S')
	{
		player->direction->x = 0;
		player->direction->y = -1;
		player->angle = 3 * PI / 2;
	}
	else if (dir == 'W')
	{
		player->direction->x = -1;
		player->direction->y = 0;
		player->angle = PI;
	}
	else if (dir == 'E')
	{
		player->direction->x = 1;
		player->direction->y = 0;
		player->angle = 0;
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

/// Set the player position and direction
/// @param cub The cub struct
/// @param i The map line
/// @param j The map column
void	set_player_pos_and_dir(t_cub *cub, int i, int j)
{
	cub->player->position->x = j;
	cub->player->position->y = i;
	set_player_direction(cub->player, cub->map[i][j]);
}

/// Check if the map has only one player
/// @param counter Number of players
/// @param map The map in a double array
/// @param cub The cub struct
void	check_player_count(int counter, char **map, t_cub *cub)
{
	if (counter != 1)
	{
		free_split(map);
		throw_err("Invalid amount of players", cub);
	}
}
