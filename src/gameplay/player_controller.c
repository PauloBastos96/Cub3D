/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:07 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/26 16:09:50 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Handle player movement
/// @param keycode The key pressed
/// @param cub The cub struct
void	movement_handler(int keycode, t_cub *cub)
{
	if (keycode == XK_w || keycode == XK_d)
	{
		cub->player->pos_x += cub->player->dir_x * PLAYER_SPEED;
		cub->player->pos_y += cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_s || keycode == XK_a)
	{
		cub->player->pos_x -= cub->player->dir_x * PLAYER_SPEED;
		cub->player->pos_y -= cub->player->dir_y * PLAYER_SPEED;
	}
	if (keycode == XK_Left)
		rotation_handler(-1, cub);
	if (keycode == XK_Right)
		rotation_handler(1, cub);
	printf("Player position: %f, %f\n", cub->player->pos_x, cub->player->pos_y);
}

/// Handle player rotation
/// @param cub The cub struct
void	rotation_handler(int direction, t_cub *cub)
{
	float	old_dir_x;

	old_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(direction * PLAYER_SPEED)
		- cub->player->dir_y * sin(direction * PLAYER_SPEED);
	cub->player->dir_y = old_dir_x * sin(direction * PLAYER_SPEED)
		+ cub->player->dir_y * cos(direction * PLAYER_SPEED);
	printf("Player direction: %f, %f\n", cub->player->dir_x, cub->player->dir_y);
}
