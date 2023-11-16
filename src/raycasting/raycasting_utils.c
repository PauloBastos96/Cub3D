/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:26:54 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 12:30:41 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Initialize values for horizontal hit calculation
/// @param cub The cub struct
/// @param vector The vector that stores the hit position
/// @param y_offset How much to increment y in each iteration
/// @param angle The angle of the ray
void	init_horizontal_values(t_cub *cub, t_vector *vector, 
	float *y_offset, float angle)
{
	if (sinf(angle) > 0)
	{
		vector->y = (int)cub->player->position->y * MAP_SCALE - 1;
		*y_offset = -MAP_SCALE;
	}
	else
	{
		vector->y = (int)cub->player->position->y * MAP_SCALE + MAP_SCALE;
		*y_offset = MAP_SCALE;
	}
}

/// Initialize values for vertical hit calculation
/// @param cub The cub struct
/// @param vector The vector that stores the hit position
/// @param x_offset How much to increment x in each iteration
/// @param angle The angle of the ray
void	init_vertical_values(t_cub *cub, t_vector *vector, 
	float *x_offset, float angle)
{
	if (cosf(angle) > 0)
	{
		vector->x = (int)cub->player->position->x * MAP_SCALE + MAP_SCALE;
		*x_offset = MAP_SCALE;
	}
	else
	{
		vector->x = (int)cub->player->position->x * MAP_SCALE - 1;
		*x_offset = -MAP_SCALE;
	}
}

/// Set values according to the distance
/// @param cub The cub struct
/// @param ray The ray struct
/// @param coords The coordinates of the hit
/// @param vert If the ray is vertical
void	distance_checks(t_cub *cub, t_ray *ray, t_vector coords, bool vert)
{
	cub->prop_y = coords.y / MAP_SCALE;
	cub->prop_x = coords.x / MAP_SCALE;
	if (!vert)
		ray->x_pos = (int)coords.x % MAP_SCALE;
	else
		ray->x_pos = (int)coords.y % MAP_SCALE;
	ray->is_vert = vert;
	draw_ray_from_player(cub, coords.x, coords.y, ray->angle);
}
