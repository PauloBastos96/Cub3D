/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:19:23 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/03 13:42:54 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	horizontal_hits(t_cub *cub, float *x, float *y, float angle)
{
	float	x_offset;
	float	y_offset;
	bool	hit;

	y_offset = 0;
	if (sinf(angle) > 0)
	{
		*y = (int)cub->player->pos_y * MAP_SCALE - 1;
		y_offset = -MAP_SCALE;
	}
	if (sinf(angle) < 0)
	{
		*y = (int)cub->player->pos_y * MAP_SCALE + MAP_SCALE;
		y_offset = MAP_SCALE;
	}
	*x = cub->player->pos_x * MAP_SCALE + ((cub->player->pos_y * MAP_SCALE - *y) / tanf(angle));
	x_offset = MAP_SCALE / tanf(angle);
	hit = false;
	while (!hit && *x >= 0 && *x < cub->width * MAP_SCALE && *y >= 0 && *y < cub->height * MAP_SCALE)
	{
		if (cub->map[(int)(*y / MAP_SCALE)][(int)(*x / MAP_SCALE)] == '1')
			hit = true;
		else
		{
			if (sinf(angle) > 0)
				*x += x_offset;
			else
				*x -= x_offset;
			*y += y_offset;
		}
	}
}

void	vertical_hits(t_cub *cub, float *x, float *y, float angle)
{
	float	x_offset;
	float	y_offset;
	bool	hit;

	x_offset = 0;
	if (cosf(angle) > 0)
	{
		*x = (int)cub->player->pos_x * MAP_SCALE + MAP_SCALE;
		x_offset = MAP_SCALE;
	}
	if (cosf(angle) < 0)
	{
		*x = (int)cub->player->pos_x * MAP_SCALE - 1;
		x_offset = -MAP_SCALE;
	}
	*y = cub->player->pos_y * MAP_SCALE + ((cub->player->pos_x * MAP_SCALE - *x) * tanf(angle));
	y_offset = MAP_SCALE * tanf(angle);
	hit = false;
	while (!hit && *x >= 0 && *x < cub->width * MAP_SCALE && *y >= 0 && *y < cub->height * MAP_SCALE)
	{
		if (cub->map[(int)(*y / MAP_SCALE)][(int)(*x / MAP_SCALE)] == '1')
			hit = true;
		else
		{
			*x += x_offset;
			if (cosf(angle) > 0)
				*y -= y_offset;
			else
				*y += y_offset;
		}
	}
}

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2)));
}

float	clamp(float n, float min, float max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}


void	draw_ray_from_player(t_cub *cub, float x, float y, float angle)
{
	float	ray_x;
	float	ray_y;
	float	dist;

	ray_x = cub->player->pos_x * MAP_SCALE;
	ray_y = cub->player->pos_y * MAP_SCALE;
	dist = get_distance(ray_x, ray_y, x, y);
	while (dist > 0)
	{
		set_pixel_color(cub->frame_buffer, ray_x, ray_y, 0x00ff00);
		ray_x += cosf(angle);
		ray_y -= sinf(angle);
		dist--;
	}
}

void	raycasting(t_cub *cub, float angle)
{
	float	v_dist;
	float	h_dist;
	float	v_x;
	float	v_y;
	float	h_x;
	float	h_y;

	printf("dir_x: %f\n", cub->player->dir_x);
	printf("dir_y: %f\n", cub->player->dir_y);
	printf("pos_x: %f\n", cub->player->pos_x);
	printf("pos_y: %f\n", cub->player->pos_y);

	vertical_hits(cub, &v_x, &v_y, angle);
	horizontal_hits(cub, &h_x, &h_y, angle);

	v_dist = get_distance(cub->player->pos_x * MAP_SCALE, cub->player->pos_y * MAP_SCALE, v_x, v_y);
	h_dist = get_distance(cub->player->pos_x * MAP_SCALE, cub->player->pos_y * MAP_SCALE, h_x, h_y);

	v_x = clamp(v_x, 0, cub->width * MAP_SCALE - 1);
	v_y = clamp(v_y, 0, cub->height * MAP_SCALE - 1);
	h_x = clamp(h_x, 0, cub->width * MAP_SCALE - 1);
	h_y = clamp(h_y, 0, cub->height * MAP_SCALE - 1);

	printf("h_dist: %f\n", v_dist);
	printf("v_dist: %f\n", h_dist);
	printf("Angle : %f rads (%fº)\n", cub->player->p_angle,
		cub->player->p_angle * (180 / PI));
	if (h_dist < v_dist)
	{
		if (cub->map[(int)h_y / MAP_SCALE][(int)h_x / MAP_SCALE] == '1')
			printf("wall at x:%f, y:%f\n", h_x, h_y);
		draw_ray_from_player(cub, h_x, h_y, angle);
	}
	else
	{
		if (cub->map[(int)v_y / MAP_SCALE][(int)v_x / MAP_SCALE] == '1')
			printf("wall at x:%f, y:%f\n", v_x, v_y);
		draw_ray_from_player(cub, v_x, v_y, angle);
	}
	printf("hx: %f, hy: %f\n", h_x, h_y);
	printf("vx: %f, vy: %f\n", v_x, v_y);
	printf("h_dist: %f\n", h_dist);
	printf("v_dist: %f\n", v_dist);
}

void	raycast_in_fov(t_cub *cub)
{
	float	angle;
	float	fov;
	float	step;

	fov = deg_to_rad(FOV);
	step = fov / 100;
	angle = cub->player->p_angle - (fov / 2);
	while (angle < cub->player->p_angle + (fov / 2))
	{
		raycasting(cub, angle);
		angle += step;
	}
	// raycasting(cub, cub->player->p_angle);
}
