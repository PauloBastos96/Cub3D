/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:11:53 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/14 13:44:05 by ffilipe-         ###   ########.fr       */
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

	pos_x = cub->player->position->x;
	if (direction == UP)
		pos_x -= cub->player->direction->x * PLAYER_SPEED + 0.2f;
	if (direction == DOWN)
		pos_x += cub->player->direction->x * PLAYER_SPEED + 0.2f;
	if (direction == RIGHT)
		pos_x += cub->player->direction->x * PLAYER_SPEED + 0.2f;
	if (direction == LEFT)
		pos_x -= cub->player->direction->x * PLAYER_SPEED + 0.2f;
	return (pos_x);
}

/// Get the next y position of the player
/// @param cub The cub struct
/// @param direction The direction the player is trying to move
/// @return The next y position of the player rounded
float	get_next_player_y_pos(t_cub *cub, enum e_direction direction)
{
	float	pos_y;

	pos_y = cub->player->position->y;
	if (direction == UP)
		pos_y -= cub->player->direction->y * PLAYER_SPEED + 0.2f;
	if (direction == DOWN)
		pos_y += cub->player->direction->y * PLAYER_SPEED + 0.2f;
	if (direction == RIGHT)
		pos_y -= cub->player->direction->y * PLAYER_SPEED + 0.2f;
	if (direction == LEFT)
		pos_y += cub->player->direction->y * PLAYER_SPEED + 0.2f;
	return (pos_y);
}

/// Check if the player is trying to move into a wall
/// @param cub The cub struct
/// @return true if the player is trying to move into a wall, false otherwise
bool	is_wall(t_cub *cub, int pos_x, int pos_y)
{
	if (pos_x < 0 || pos_x >= cub->width || pos_y < 0 || pos_y >= cub->height)
		return (true);
	if (cub->map[pos_y][pos_x] == '1' || cub->map[pos_y][pos_x] == 'D')
		return (true);
	return (false);
}
