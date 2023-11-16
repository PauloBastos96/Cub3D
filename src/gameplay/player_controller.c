/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:07 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 21:56:22 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/// Test for collision slightly to the left and right of the player
/// @param keycode The key pressed
/// @param cub The cub struct
/// @param new_pos The new position of the player
/// @param angle The angle of the collision test
/// @return true if there is a collision, false otherwise
bool	test_direction(int keycode, t_cub *cub,
	t_vector new_pos, float angle)
{
	if (keycode == XK_w)
	{
		new_pos.x += cos(cub->player->angle + angle) * PLAYER_SPEED;
		new_pos.y -= sin(cub->player->angle + angle) * PLAYER_SPEED;
	}
	if (keycode == XK_d)
	{
		new_pos.x += sin(cub->player->angle) * PLAYER_SPEED;
		new_pos.y += cos(cub->player->angle) * PLAYER_SPEED;
	}
	if (keycode == XK_s)
	{
		new_pos.x -= cos(cub->player->angle + angle) * PLAYER_SPEED;
		new_pos.y += sin(cub->player->angle + angle) * PLAYER_SPEED;
	}
	if (keycode == XK_a)
	{
		new_pos.x -= sin(cub->player->angle) * PLAYER_SPEED;
		new_pos.y -= cos(cub->player->angle) * PLAYER_SPEED;
	}
	return (is_wall(cub, new_pos.x, new_pos.y));
}

/// Test for collision in front of the player
/// @param keycode The key pressed
/// @param cub The cub struct
/// @param new_pos The new position of the player
/// @return true if there is a collision, false otherwise
bool	test_front(int keycode, t_cub *cub, t_vector *new_pos)
{
	if (keycode == XK_w)
	{
		new_pos->x += cub->player->direction->x * PLAYER_SPEED;
		new_pos->y -= cub->player->direction->y * PLAYER_SPEED;
	}
	if (keycode == XK_d)
	{
		new_pos->x += cub->player->direction->y * PLAYER_SPEED;
		new_pos->y += cub->player->direction->x * PLAYER_SPEED;
	}
	if (keycode == XK_s)
	{
		new_pos->x -= cub->player->direction->x * PLAYER_SPEED;
		new_pos->y += cub->player->direction->y * PLAYER_SPEED;
	}
	if (keycode == XK_a)
	{
		new_pos->x -= sin(cub->player->angle) * PLAYER_SPEED;
		new_pos->y -= cos(cub->player->angle) * PLAYER_SPEED;
	}
	return (is_wall(cub, new_pos->x, new_pos->y));
}

/// Handle player movement
/// @param keycode The key pressed
/// @param cub The cub struct
void	movement_handler(int keycode, t_cub *cub)
{
	t_vector	new_pos;

	new_pos.x = cub->player->position->x;
	new_pos.y = cub->player->position->y;
	if (!test_direction(keycode, cub, new_pos, deg_to_rad(45))
		&& !test_direction(keycode, cub, new_pos, deg_to_rad(-45))
		&& !test_front(keycode, cub, &new_pos))
	{
		cub->player->position->x = new_pos.x;
		cub->player->position->y = new_pos.y;
	}
	if (keycode == XK_e)
	{
		new_pos.y = get_next_player_y_pos(cub, UP);
		new_pos.x = get_next_player_x_pos(cub, UP);
		if (cub->map[(int)new_pos.y][(int)new_pos.x] == 'D')
		{
			cub->map[(int)new_pos.y][(int)new_pos.x] = '0';
		}
	}
	if (keycode == XK_Left)
		rotation_handler(-1, cub, ROTATION_SPEED);
	if (keycode == XK_Right)
		rotation_handler(1, cub, ROTATION_SPEED);
}

/// Handle player rotation
/// @param direction The direction of the rotation
/// @param cub The cub struct
/// @param speed The speed of the rotation
void	rotation_handler(int direction, t_cub *cub, float speed)
{
	if (direction == -1)
	{
		cub->player->angle += speed;
		if (cub->player->angle > 2 * PI)
			cub->player->angle -= 2 * PI;
	}
	else if (direction == 1)
	{
		cub->player->angle -= speed;
		if (cub->player->angle < 0)
			cub->player->angle += 2 * PI;
	}
	cub->player->direction->x = cos(cub->player->angle);
	cub->player->direction->y = sin(cub->player->angle);
}
