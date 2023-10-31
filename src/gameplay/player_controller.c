/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:07 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/31 15:17:12 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Handle player movement
/// @param keycode The key pressed
/// @param cub The cub struct
///? Add support for diagonal movement
void	movement_handler(int keycode, t_cub *cub)
{
	if (keycode == XK_w && !is_wall(cub, UP))
	{
		cub->player->pos_x += cub->player->dir_x * PLAYER_SPEED;
		cub->player->pos_y -= cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_d && !is_wall(cub, RIGHT))
	{
		cub->player->pos_x += cub->player->dir_y * PLAYER_SPEED;
		cub->player->pos_y += cub->player->dir_x * PLAYER_SPEED;
	}
	if ((keycode == XK_s) && !is_wall(cub, DOWN))
	{
		cub->player->pos_x -= cub->player->dir_x * PLAYER_SPEED;
		cub->player->pos_y += cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_a && !is_wall(cub, LEFT))
	{
		cub->player->pos_x -= cub->player->dir_y * PLAYER_SPEED;
		cub->player->pos_y -= cub->player->dir_x * PLAYER_SPEED;
	}
	if (keycode == XK_Left)
		rotation_handler(-1, cub);
	if (keycode == XK_Right)
		rotation_handler(1, cub);
	//raycasting(cub);
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
