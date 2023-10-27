/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:07 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/27 18:38:15 by paulorod         ###   ########.fr       */
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
		cub->player->pos_x -= cub->player->dir_x * PLAYER_SPEED;
		cub->player->pos_y -= cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_d && !is_wall(cub, RIGHT))
	{
		cub->player->pos_x += cub->player->dir_y * PLAYER_SPEED;
		cub->player->pos_y -= cub->player->dir_x * PLAYER_SPEED;
	}
	if ((keycode == XK_s) && !is_wall(cub, DOWN))
	{
		cub->player->pos_x += cub->player->dir_x * PLAYER_SPEED;
		cub->player->pos_y += cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_a && !is_wall(cub, LEFT))
	{
		cub->player->pos_x -= cub->player->dir_y * PLAYER_SPEED;
		cub->player->pos_y += cub->player->dir_x * PLAYER_SPEED;
	}
	if (keycode == XK_Left)
		rotation_handler(-1, cub);
	if (keycode == XK_Right)
		rotation_handler(1, cub);
	printf("x: %f, y: %f\n", cub->player->pos_x, cub->player->pos_y);
}

/// Handle player rotation
/// @param cub The cub struct
void	rotation_handler(int direction, t_cub *cub)
{
	float	old_dir_x;

	old_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(direction * ROTATION_SPEED)
		- cub->player->dir_y * sin(direction * ROTATION_SPEED);
	cub->player->dir_y = old_dir_x * sin(direction * ROTATION_SPEED)
		+ cub->player->dir_y * cos(direction * ROTATION_SPEED);
}
