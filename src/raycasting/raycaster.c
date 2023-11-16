/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:19:23 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/16 21:58:27 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

///Test hit for wall colision
/// @param cub The cub struct
/// @param vector The vector that stores the hit position
/// @param angle The angle of the ray
/// @return true if the ray hit a wall, false otherwise
bool	check_colision(t_cub *cub, t_vector vector, float angle, bool vert)
{
	(void)vert;
	if (rad_to_deg(angle) < 180)
		vector.y = ceil(vector.y) / MAP_SCALE;
	else
		vector.y = floor(vector.y) / MAP_SCALE;
	if (rad_to_deg(angle) >= 90 && rad_to_deg(angle) <= 270)
		vector.x = ceil(vector.x) / MAP_SCALE;
	else
		vector.x = floor(vector.x) / MAP_SCALE;
	vector.x = clamp(vector.x, 0, cub->width - 1);
	vector.y = clamp(vector.y, 0, cub->height - 1);
	if (ft_strchr("12D", cub->map[(int)vector.y][(int)vector.x]))
		return (true);
	return (false);
}

///Test for horizontal hits
/// @param cub The cub struct
/// @param vector The vector that stores the hit position
/// @param angle The angle of the ray
void	horizontal_hits(t_cub *cub, t_vector *vector, float angle)
{
	float	x_offset;
	float	y_offset;

	y_offset = 0;
	init_horizontal_values(cub, vector, &y_offset, angle);
	vector->x = cub->player->position->x * MAP_SCALE
		+ ((cub->player->position->y * MAP_SCALE - vector->y) / tanf(angle));
	x_offset = MAP_SCALE / tanf(angle);
	while (vector->x >= 0 && vector->x < cub->width * MAP_SCALE
		&& vector->y >= 0 && vector->y < cub->height * MAP_SCALE)
	{
		if (check_colision(cub, *vector, angle, false))
			break ;
		else
		{
			if (sinf(angle) > 0)
				vector->x += x_offset;
			else
				vector->x -= x_offset;
			vector->y += y_offset;
		}
	}
}

///Test for vertical hits
/// @param cub The cub struct
/// @param vector The vector that stores the hit position
/// @param angle The angle of the ray
void	vertical_hits(t_cub *cub, t_vector *vector, float angle)
{
	float	x_offset;
	float	y_offset;

	x_offset = 0;
	init_vertical_values(cub, vector, &x_offset, angle);
	vector->y = cub->player->position->y * MAP_SCALE
		+ ((cub->player->position->x * MAP_SCALE - vector->x) * tanf(angle));
	y_offset = MAP_SCALE * tanf(angle);
	while (vector->x >= 0 && vector->x < cub->width * MAP_SCALE
		&& vector->y >= 0 && vector->y < cub->height * MAP_SCALE)
	{
		if (check_colision(cub, *vector, angle, true))
			break ;
		else
		{
			vector->x += x_offset;
			if (cosf(angle) > 0)
				vector->y -= y_offset;
			else
				vector->y += y_offset;
		}
	}
}

/// Raycasting
/// @param cub The cub struct 
/// @param ray The ray struct
/// @param i The pixel column index
void	raycasting(t_cub *cub, t_ray *ray, int i)
{
	float		v_dist;
	float		h_dist;
	t_vector	vertical;
	t_vector	horizontal;
	t_vector	player_pos;

	player_pos.x = cub->player->position->x * MAP_SCALE;
	player_pos.y = cub->player->position->y * MAP_SCALE;
	vertical_hits(cub, &vertical, ray->angle);
	horizontal_hits(cub, &horizontal, ray->angle);
	v_dist = get_distance(player_pos, vertical);
	h_dist = get_distance(player_pos, horizontal);
	vertical.x = clamp(vertical.x, 0, cub->width * MAP_SCALE - 1);
	vertical.y = clamp(vertical.y, 0, cub->height * MAP_SCALE - 1);
	horizontal.x = clamp(horizontal.x, 0, cub->width * MAP_SCALE - 1);
	horizontal.y = clamp(horizontal.y, 0, cub->height * MAP_SCALE - 1);
	if (h_dist < v_dist)
		distance_checks(cub, ray, horizontal, false);
	else
		distance_checks(cub, ray, vertical, true);
	ray->distance = get_min(h_dist, v_dist);
	draw_walls(cub, *ray, i);
}

/// Raycast in the field of view
/// @param cub The cub struct
void	raycast_in_fov(t_cub *cub)
{
	float	fov;
	float	step;
	int		i;
	t_ray	ray;

	i = WINDOW_WIDTH;
	fov = deg_to_rad(FOV);
	step = fov / WINDOW_WIDTH;
	ray.angle = cub->player->angle - (fov / 2);
	if (ray.angle < 0)
		ray.angle += 2 * PI;
	while (i > 0)
	{
		raycasting(cub, &ray, i);
		ray.angle += step;
		if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		i--;
	}
	if (cub->show_minimap)
		cpy_img_to_frame_buffer(cub->frame_buffer, *cub->minimap, 0, 0);
}
