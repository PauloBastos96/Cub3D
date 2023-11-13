/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:19:23 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/13 12:39:34 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	check_colision(t_cub *cub, t_vector vector, float angle, int i, bool vert)
{
	(void)i;
	(void)vert;
	// if (cub->debug_line == i)
	// 	printf("x: %f(%f), y: %f(%f), angle: %f			", vector.x / MAP_SCALE, vector.x, vector.y / MAP_SCALE, vector.y, rad_to_deg(angle));
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
	if (cub->map[(int)(vector.y / MAP_SCALE)][(int)(vector.x / MAP_SCALE)] == '1')
	{
		// if (cub->debug_line == i)
		// 	printf("wall (%f, %f) (%f, %f) | %s\n", vector.x / MAP_SCALE, vector.y / MAP_SCALE, vector.x, vector.y, vert ? "vertical" : "horizontal");
		return (true);
	}
	// if (cub->debug_line == i)
	// 	printf("not wall (%f, %f) (%f, %f) | %s\n", vector.x / MAP_SCALE, vector.y / MAP_SCALE, vector.x, vector.y, vert ? "vertical" : "horizontal");
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
	if (sinf(angle) < 0)
	{
		vector->y = (int)cub->player->position->y * MAP_SCALE + MAP_SCALE;
		y_offset = MAP_SCALE;
	}
	vector->x = cub->player->position->x * MAP_SCALE + ((cub->player->position->y * MAP_SCALE - vector->y) / tanf(angle));
	x_offset = MAP_SCALE / tanf(angle);
	hit = false;
	while (!hit && vector->x >= 0 && vector->x < cub->width * MAP_SCALE && vector->y >= 0 && vector->y < cub->height * MAP_SCALE)
	{
		if (check_colision(cub, *vector, angle, i, false))
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
	if (cosf(angle) < 0)
	{
		vector->x = (int)cub->player->position->x * MAP_SCALE - 1;
		x_offset = -MAP_SCALE;
	}
	vector->y = cub->player->position->y * MAP_SCALE + ((cub->player->position->x * MAP_SCALE - vector->x) * tanf(angle));
	y_offset = MAP_SCALE * tanf(angle);
	hit = false;
	while (!hit && vector->x >= 0 && vector->x < cub->width * MAP_SCALE && vector->y >= 0 && vector->y < cub->height * MAP_SCALE)
	{
		if (check_colision(cub, *vector, angle, i, true))
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

void	raycasting(t_cub *cub, float angle, int i)
{
	float		v_dist;
	float		h_dist;
	t_vector	vertical;
	t_vector	horizontal;
	t_vector	player_pos;
	int			x;
	bool		is_vert;

	player_pos.x = cub->player->position->x * MAP_SCALE;
	player_pos.y = cub->player->position->y * MAP_SCALE;
	vertical_hits(cub, &vertical, angle, i);
	horizontal_hits(cub, &horizontal, angle, i);
	v_dist = get_distance(player_pos, vertical);
	h_dist = get_distance(player_pos, horizontal);

	vertical.x = clamp(vertical.x, 0, cub->width * MAP_SCALE - 1);
	vertical.y = clamp(vertical.y, 0, cub->height * MAP_SCALE - 1);
	horizontal.x = clamp(horizontal.x, 0, cub->width * MAP_SCALE - 1);
	horizontal.y = clamp(horizontal.y, 0, cub->height * MAP_SCALE - 1);
	if (h_dist < v_dist)
	{
		x = (int)horizontal.x % MAP_SCALE;
		is_vert = false;
		draw_ray_from_player(cub, horizontal.x, horizontal.y, angle);
	}
	else
	{
		x = (int)vertical.y % MAP_SCALE;
		is_vert = true;
		draw_ray_from_player(cub, vertical.x, vertical.y, angle);
	}
	// if (cub->debug_line == i)
	// 	printf("p_line: %d, h_dist: %f, v_dist: %f, \
	// 		h_x: %f, h_y: %f, v_x: %f, v_y: %f\n",
	// 		i, h_dist, v_dist, horizontal.x / MAP_SCALE,
	// 		horizontal.y / MAP_SCALE, vertical.x / MAP_SCALE,
	// 		vertical.y / MAP_SCALE);
	draw_walls(cub, get_min(h_dist, v_dist), angle, i, x, is_vert);
}

void	raycast_in_fov(t_cub *cub)
{
	float	angle;
	float	fov;
	float	step;
	int		i;

	i = WINDOW_WIDTH;
	fov = deg_to_rad(FOV);
	step = fov / WINDOW_WIDTH;
	angle = cub->player->angle - (fov / 2);
	if (angle < 0)
		angle += 2 * PI;
	if (cub->show_minimap)
		display_map(cub);
	while (i > 0)
	{
		raycasting(cub, angle, i);
		angle += step;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		i--;
	}
	if (cub->show_minimap)
		cpy_img_to_frame_buffer(cub->frame_buffer, *cub->minimap, 0, 0);
}
