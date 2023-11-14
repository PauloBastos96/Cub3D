/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:07 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/14 15:26:34 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

bool	test_left(int keycode, t_cub *cub, t_vector new_pos)
{
	if (keycode == XK_w)
	{
		new_pos.x += cos(cub->player->angle - 45) * PLAYER_SPEED;
		new_pos.y -= sin(cub->player->angle - 45) * PLAYER_SPEED;
	}
	if (keycode == XK_d)
	{
		new_pos.x += sin(cub->player->angle) * PLAYER_SPEED;
		new_pos.y += cos(cub->player->angle) * PLAYER_SPEED;
	}
	if (keycode == XK_s)
	{
		new_pos.x -= cos(cub->player->angle - 45) * PLAYER_SPEED;
		new_pos.y += sin(cub->player->angle - 45) * PLAYER_SPEED;
	}
	if (keycode == XK_a)
	{
		new_pos.x -= cub->player->direction->y * PLAYER_SPEED;
		new_pos.y -= cub->player->direction->x * PLAYER_SPEED;
	}
	return (is_wall(cub, new_pos.x, new_pos.y));
}

bool	test_right(int keycode, t_cub *cub, t_vector new_pos)
{
	if (keycode == XK_w)
	{
		new_pos.x += cos(cub->player->angle + 45) * PLAYER_SPEED;
		new_pos.y -= sin(cub->player->angle + 45) * PLAYER_SPEED;
	}
	if (keycode == XK_d)
	{
		new_pos.x += sin(cub->player->angle) * PLAYER_SPEED;
		new_pos.y += cos(cub->player->angle) * PLAYER_SPEED;
	}
	if (keycode == XK_s)
	{
		new_pos.x -= cos(cub->player->angle + 45) * PLAYER_SPEED;
		new_pos.y += sin(cub->player->angle + 45) * PLAYER_SPEED;
	}
	if (keycode == XK_a)
	{
		new_pos.x -= sin(cub->player->angle) * PLAYER_SPEED;
		new_pos.y -= cos(cub->player->angle) * PLAYER_SPEED;
	}
	return (is_wall(cub, new_pos.x, new_pos.y));
}

/// Handle player movement
/// @param keycode The key pressed
/// @param cub The cub struct
///? Add support for diagonal movement
void	movement_handler(int keycode, t_cub *cub)
{
	t_vector	new_pos;

	new_pos.x = cub->player->position->x;
	new_pos.y = cub->player->position->y;
	if (!test_right(keycode, cub, new_pos) 
		&& !test_left(keycode, cub, new_pos) 
		&& !test_front(keycode, cub, &new_pos))
	{
		cub->player->position->x = new_pos.x;
		cub->player->position->y = new_pos.y;
	}
	if(keycode == XK_e)
	{
		new_pos.y = get_next_player_y_pos(cub, UP);
		new_pos.x = get_next_player_x_pos(cub, UP);
		if(cub->map[(int)new_pos.y][(int)new_pos.x] == 'D')
		{
			cub->map[(int)new_pos.y][(int)new_pos.x] = '0';
		}
	}
	if (keycode == XK_Left)
		rotation_handler(-1, cub);
	if (keycode == XK_Right)
		rotation_handler(1, cub);
}

/// Handle player rotation
/// @param cub The cub struct
void	rotation_handler(int direction, t_cub *cub)
{
	if (direction == -1)
	{
		cub->player->angle += ROTATION_SPEED;
		if (cub->player->angle > 2 * PI)
			cub->player->angle -= 2 * PI;
	}
	else if (direction == 1)
	{
		cub->player->angle -= ROTATION_SPEED;
		if (cub->player->angle < 0)
			cub->player->angle += 2 * PI;
	}
	cub->player->direction->x = cos(cub->player->angle);
	cub->player->direction->y = sin(cub->player->angle);
}
