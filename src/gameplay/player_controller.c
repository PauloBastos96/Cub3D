/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:07 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/07 15:13:48 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	test_front(int keycode, t_cub *cub, t_vector *new_pos)
{
	if (keycode == XK_w)
	{
		new_pos->x += cub->player->dir_x * PLAYER_SPEED;
		new_pos->y -= cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_d)
	{
		new_pos->x += cub->player->dir_y * PLAYER_SPEED;
		new_pos->y += cub->player->dir_x * PLAYER_SPEED;
	}
	if (keycode == XK_s)
	{
		new_pos->x -= cub->player->dir_x * PLAYER_SPEED;
		new_pos->y += cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_a)
	{
		new_pos->x -= sin(cub->player->p_angle) * PLAYER_SPEED;
		new_pos->y -= cos(cub->player->p_angle) * PLAYER_SPEED;
	}
	return (is_wall(cub, new_pos->x, new_pos->y));
}
bool	test_left(int keycode, t_cub *cub, t_vector new_pos)
{
	if (keycode == XK_w)
	{
		new_pos.x += cos(cub->player->p_angle - 45) * PLAYER_SPEED;
		new_pos.y -= sin(cub->player->p_angle - 45) * PLAYER_SPEED;
	}
	if (keycode == XK_d)
	{
		new_pos.x += sin(cub->player->p_angle) * PLAYER_SPEED;
		new_pos.y += cos(cub->player->p_angle) * PLAYER_SPEED;
	}
	if (keycode == XK_s)
	{
		new_pos.x -= cos(cub->player->p_angle - 45) * PLAYER_SPEED;
		new_pos.y += sin(cub->player->p_angle - 45) * PLAYER_SPEED;
	}
	if (keycode == XK_a)
	{
		new_pos.x -= cub->player->dir_y * PLAYER_SPEED;
		new_pos.y -= cub->player->dir_x * PLAYER_SPEED;
	}
	return (is_wall(cub, new_pos.x, new_pos.y));
}

bool	test_right(int keycode, t_cub *cub, t_vector new_pos)
{
	if (keycode == XK_w)
	{
		new_pos.x += cos(cub->player->p_angle + 45) * PLAYER_SPEED;
		new_pos.y -= sin(cub->player->p_angle + 45) * PLAYER_SPEED;
	}
	if (keycode == XK_d)
	{
		new_pos.x += sin(cub->player->p_angle) * PLAYER_SPEED;
		new_pos.y += cos(cub->player->p_angle) * PLAYER_SPEED;
	}
	if (keycode == XK_s)
	{
		new_pos.x -= cos(cub->player->p_angle + 45) * PLAYER_SPEED;
		new_pos.y += sin(cub->player->p_angle + 45) * PLAYER_SPEED;
	}
	if (keycode == XK_a)
	{
		new_pos.x -= sin(cub->player->p_angle) * PLAYER_SPEED;
		new_pos.y -= cos(cub->player->p_angle) * PLAYER_SPEED;
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

	new_pos.x = cub->player->pos_x;
	new_pos.y = cub->player->pos_y;
	
	if (!test_right(keycode, cub, new_pos) 
		&& !test_left(keycode, cub, new_pos) 
		&& !test_front(keycode, cub, &new_pos))
	{
		cub->player->pos_x = new_pos.x;
		cub->player->pos_y = new_pos.y;
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
		cub->player->p_angle += ROTATION_SPEED;
		if (cub->player->p_angle > 2 * PI)
			cub->player->p_angle -= 2 * PI;
	}
	else if (direction == 1)
	{
		cub->player->p_angle -= ROTATION_SPEED;
		if (cub->player->p_angle < 0)
			cub->player->p_angle += 2 * PI;
	}
	cub->player->dir_x = cos(cub->player->p_angle);
	cub->player->dir_y = sin(cub->player->p_angle);
}
