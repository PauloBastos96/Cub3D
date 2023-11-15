/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:19:23 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/15 14:37:44 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	check_colision(t_cub *cub, t_vector vector, float angle, int i)
{
	if (rad_to_deg(angle) < 180)
		vector.y = ceil(vector.y);
	else
		vector.y = floor(vector.y);
	if (rad_to_deg(angle) > 90 && rad_to_deg(angle) < 270)
		vector.x = ceil(vector.x);
	else
		vector.x = floor(vector.x);
	vector.x = clamp(vector.x, 0, cub->width * MAP_SCALE - 1);
	vector.y = clamp(vector.y, 0, cub->height * MAP_SCALE - 1);
	if (ft_strchr("1BD2", cub->map[(int)(vector.y / MAP_SCALE)]
		[(int)(vector.x / MAP_SCALE)]))
		return (true);
	return (false);
}

void	horizontal_hits(t_cub *cub, t_vector *vector, float angle, int i)
{
	float	x_offset;
	float	y_offset;
	bool	hit;

	y_offset = 0;
	if (sinf(angle) > 0)
	{
		vector->y = (int)cub->player->position->y * MAP_SCALE - 1;
		y_offset = -MAP_SCALE;
	}
	else
	{
		vector->y = (int)cub->player->position->y * MAP_SCALE + MAP_SCALE;
		y_offset = MAP_SCALE;
	}
	vector->x = cub->player->position->x * MAP_SCALE + ((cub->player->position->y * MAP_SCALE - vector->y) / tanf(angle));
	x_offset = MAP_SCALE / tanf(angle);
	hit = false;
	while (!hit && vector->x >= 0 && vector->x < cub->width * MAP_SCALE && vector->y >= 0 && vector->y < cub->height * MAP_SCALE)
	{
		if (check_colision(cub, *vector, angle, i))
			hit = true;
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

void	vertical_hits(t_cub *cub, t_vector *vector, float angle, int i)
{
	float	x_offset;
	float	y_offset;
	bool	hit;

	x_offset = 0;
	if (cosf(angle) > 0)
	{
		vector->x = (int)cub->player->position->x * MAP_SCALE + MAP_SCALE;
		x_offset = MAP_SCALE;
	}
	else
	{
		vector->x = (int)cub->player->position->x * MAP_SCALE - 1;
		x_offset = -MAP_SCALE;
	}
	vector->y = cub->player->position->y * MAP_SCALE + ((cub->player->position->x * MAP_SCALE - vector->x) * tanf(angle));
	y_offset = MAP_SCALE * tanf(angle);
	hit = false;
	while (!hit && vector->x >= 0 && vector->x < cub->width * MAP_SCALE && vector->y >= 0 && vector->y < cub->height * MAP_SCALE)
	{
		if (check_colision(cub, *vector, angle, i))
			hit = true;
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
	vertical_hits(cub, &vertical, ray->angle, i);
	horizontal_hits(cub, &horizontal, ray->angle, i);
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
