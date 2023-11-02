/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:11:53 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/02 12:53:55 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Get the next player x position
/// @param cub The cub struct
/// @param direction The direction the player is trying to move
/// @return The next x position of the player rounded
float	get_next_player_x_pos(t_cub *cub, enum e_direction direction)
{
	float	pos_x;

	pos_x = cub->player->pos_x;
	if (direction == UP)
		pos_x -= cub->player->dir_x * PLAYER_SPEED + 0.2f;
	if (direction == DOWN)
		pos_x += cub->player->dir_x * PLAYER_SPEED + 0.2f;
	if (direction == RIGHT)
		pos_x += cub->player->dir_x * PLAYER_SPEED + 0.2f;
	if (direction == LEFT)
		pos_x -= cub->player->dir_x * PLAYER_SPEED + 0.2f;
	return (roundf(pos_x));
}

/// Get the next y position of the player
/// @param cub The cub struct
/// @param direction The direction the player is trying to move
/// @return The next y position of the player rounded
float	get_next_player_y_pos(t_cub *cub, enum e_direction direction)
{
	float	pos_y;

	pos_y = cub->player->pos_y;
	if (direction == UP)
		pos_y -= cub->player->dir_y * PLAYER_SPEED + 0.2f;
	if (direction == DOWN)
		pos_y += cub->player->dir_y * PLAYER_SPEED + 0.2f;
	if (direction == RIGHT)
		pos_y -= cub->player->dir_y * PLAYER_SPEED + 0.2f;
	if (direction == LEFT)
		pos_y += cub->player->dir_y * PLAYER_SPEED + 0.2f;
	return (roundf(pos_y));
}

/// Check if the player is trying to move into a wall
/// @param cub The cub struct
/// @return true if the player is trying to move into a wall, false otherwise
bool	is_wall(t_cub *cub, enum e_direction direction)
{
	int	pos_x;
	int	pos_y;

	pos_x = get_next_player_x_pos(cub, direction);
	pos_y = get_next_player_y_pos(cub, direction);
	if (pos_x < 0 || pos_x > cub->width || pos_y < 0 || pos_y > cub->height)
		return (true);
	if (cub->map[pos_y][pos_x] == '1')
		return (true);
	return (false);
}
