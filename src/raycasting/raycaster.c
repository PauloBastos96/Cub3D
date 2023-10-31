/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:19:23 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/30 20:25:40 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	raycasting(t_cub *cub)
{
	float	y;
	float	x;

	y = 0;
	x = 0;

	printf("dir_x: %f\n", cub->player->dir_x);
	printf("dir_y: %f\n", cub->player->dir_y);
	printf("pos_x: %f\n", cub->player->pos_x);
	printf("pos_y: %f\n", cub->player->pos_y);
	if (cub->player->dir_y >= 0)
	{
		y = cub->player->pos_y - 1;
		printf("y: %f\n", y);
	}
	if (cub->player->dir_y < 0)
	{
		y = cub->player->pos_y + 1;
		printf("y: %f\n", y);
	}
	printf("Angle : %f rads (%fº)\n", cub->player->p_angle, cub->player->p_angle * (180 / PI));
	x = cub->player->pos_x + ((cub->player->pos_y - y) / tanf(cub->player->p_angle));
	printf("x: %f\n", x);
	if (cub->map[(int)y][(int)x] == '1')
	{
		printf("wall\n");
		return ;
	}
}