/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:19:23 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/31 16:35:34 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	horizontal_hits(t_cub *cub, float *x, float *y)
{
	float	x_offset;
	float	y_offset;
	bool	hit;

	if (cub->player->dir_y >= 0)
	{
		*y = cub->player->pos_y - 1;
		y_offset = -1;
	}
	if (cub->player->dir_y < 0)
	{
		*y = cub->player->pos_y + 1;
		y_offset = 1;
	}
	*x = cub->player->pos_x 
		+ ((cub->player->pos_y - *y) / tanf(cub->player->p_angle));
	x_offset = 1 / tanf(cub->player->p_angle);
	hit = false;
	while (!hit && *x >= 0 && *x < cub->width && *y >= 0 && *y < cub->height)
	{
		if (cub->map[(int)*y][(int)*x] == '1')
			hit = true;
		else
		{
			*x += x_offset;
			*y += y_offset;
		}
	}
}

void	vertical_hits(t_cub *cub, float *x, float *y)
{
	float	x_offset;
	float	y_offset;
	bool	hit;

	if (cub->player->dir_x >= 0)
	{
		*x = cub->player->pos_x + 1;
		x_offset = 1;
	}
	if (cub->player->dir_x < 0)
	{
		*x = cub->player->pos_x - 1;
		x_offset = -1;
	}
	*y = cub->player->pos_y
		+ ((cub->player->pos_x - *x) * tanf(cub->player->p_angle));
	y_offset = tanf(cub->player->p_angle);
	hit = false;
	while (!hit && *x >= 0 && *x < cub->width && *y >= 0 && *y < cub->height)
	{
		if (cub->map[(int)*y][(int)*x] == '1')
			hit = true;
		else
		{
			*x += x_offset;
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


void	draw_ray_from_player(t_cub *cub, float x, float y)
{
	float	ray_x;
	float	ray_y;
	float	dist;

	ray_x = cub->player->pos_x * 10;
	ray_y = cub->player->pos_y * 10;
	dist = get_distance(ray_x, ray_y, x, y) * 10;
	while (dist > 0)
	{
		set_pixel_color(cub->frame_buffer, ray_x, ray_y, 0x00ff00);
		ray_x += cosf(cub->player->p_angle);
		ray_y -= sinf(cub->player->p_angle);
		dist--;
	}
}

void	raycasting(t_cub *cub)
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

	vertical_hits(cub, &v_x, &v_y);
	horizontal_hits(cub, &h_x, &h_y);

	v_dist = get_distance(cub->player->pos_x, cub->player->pos_y, v_x, v_y);
	h_dist = get_distance(cub->player->pos_x, cub->player->pos_y, h_x, h_y);

	v_x = clamp(v_x, 0, cub->width - 1);
	v_y = clamp(v_y, 0, cub->height - 1);
	h_x = clamp(h_x, 0, cub->width - 1);
	h_y = clamp(h_y, 0, cub->height - 1);

	printf("h_dist: %f\n", v_dist);
	printf("v_dist: %f\n", h_dist);
	printf("Angle : %f rads (%fº)\n", cub->player->p_angle, 
		cub->player->p_angle * (180 / PI));
	if (h_dist < v_dist)
	{
		if (cub->map[(int)h_y][(int)h_x] == '1')
			printf("wall at x:%f, y:%f\n", v_x, h_y);
		draw_ray_from_player(cub, v_x, h_y);
	}
	else
	{
		if (cub->map[(int)v_y][(int)v_x] == '1')
			printf("wall at x:%f, y:%f\n", v_x, h_y);
		draw_ray_from_player(cub, v_x, h_y);
	}
}
