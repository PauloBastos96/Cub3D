/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:19:23 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/07 15:25:48 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	check_colision(t_cub *cub, float x, float y, float angle)
{
	if (x > (int)x && cosf(angle) < 0)
		x += 1;
	if (y > (int)y && sinf(angle) > 0)
		y += 1;
	x = clamp(x, 0, cub->width * MAP_SCALE - 1);
	y = clamp(y, 0, cub->height * MAP_SCALE - 1);
	if (cub->map[(int)(y / MAP_SCALE)][(int)(x / MAP_SCALE)] == '1')
		return (true);
	return (false);
}

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
		if (check_colision(cub, *x, *y, angle))
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
		if (check_colision(cub, *x, *y, angle))
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
	return (sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2)));
}

void	draw_ray_from_player(t_cub *cub, float x, float y, float angle)
{
	float	ray_x;
	float	ray_y;
	float	dist;

	ray_x = cub->player->pos_x * MINIMAP_SCALE;
	ray_y = cub->player->pos_y * MINIMAP_SCALE;
	dist = get_distance(ray_x, ray_y, x / MAP_SCALE * MINIMAP_SCALE, 
			y / MAP_SCALE * MINIMAP_SCALE);
	while (dist > 0)
	{
		set_pixel_color(cub->minimap, ray_x, ray_y, 0x00ff00);
		ray_x += cosf(angle);
		ray_y -= sinf(angle);
		dist--;
	}
	set_pixel_color(cub->minimap, ray_x, ray_y, 0xff0000);
}

void	draw_walls(t_cub *cub, float dist, float angle, int i, int color)
{
	int		p_height;
	float	p_plane;
	int		d_start;
	int		d_end;

	p_plane = (WINDOW_WIDTH / 2) / tanf(deg_to_rad(FOV / 2));
	p_height = (MAP_SCALE / (dist * cosf(cub->player->p_angle - angle))) * p_plane;
	d_start = (-p_height / 2) + (WINDOW_HEIGHT / 2);
	d_end = (p_height / 2) + (WINDOW_HEIGHT / 2);
	if (d_start < 0)
		d_start = 0;
	if (d_end >= WINDOW_HEIGHT)
		d_end = WINDOW_HEIGHT - 1;
	while (d_start < d_end)
	{
		set_pixel_color(cub->frame_buffer, i, d_start, color);
		d_start++;
	}
}

float	get_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

void	raycasting(t_cub *cub, float angle, int i)
{
	float	v_dist;
	float	h_dist;
	float	v_x;
	float	v_y;
	float	h_x;
	float	h_y;
	int		color;

	vertical_hits(cub, &v_x, &v_y, angle);
	horizontal_hits(cub, &h_x, &h_y, angle);
	v_dist = get_distance(cub->player->pos_x * MAP_SCALE, cub->player->pos_y * MAP_SCALE, v_x, v_y);
	h_dist = get_distance(cub->player->pos_x * MAP_SCALE, cub->player->pos_y * MAP_SCALE, h_x, h_y);

	v_x = clamp(v_x, 0, cub->width * MAP_SCALE - 1);
	v_y = clamp(v_y, 0, cub->height * MAP_SCALE - 1);
	h_x = clamp(h_x, 0, cub->width * MAP_SCALE - 1);
	h_y = clamp(h_y, 0, cub->height * MAP_SCALE - 1);
	if (h_dist < v_dist)
	{
		color = 0xff0000;
		draw_ray_from_player(cub, h_x, h_y, angle);
	}
	else
	{
		color = 0xA30000;
		draw_ray_from_player(cub, v_x, v_y, angle);
	}
	draw_walls(cub, get_min(h_dist, v_dist), angle, i, color);
}



void	draw_floor(t_cub *cub)
{
	int	i;
	int	j;

	i = WINDOW_HEIGHT / 2;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			set_pixel_color(cub->frame_buffer, j, i, rgb_to_int(cub->floor_color));
			j++;
		}
		i++;
	}
}

void draw_ceiling(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			set_pixel_color(cub->frame_buffer, j, i, rgb_to_int(cub->ceiling_color));
			j++;
		}
		i++;
	}
}

void	raycast_in_fov(t_cub *cub)
{
	float	angle;
	float	fov;
	float	step;
	int		i;

	draw_floor(cub);
	draw_ceiling(cub);
	i = WINDOW_WIDTH;
	fov = deg_to_rad(FOV);
	step = fov / WINDOW_WIDTH;
	angle = cub->player->p_angle - (fov / 2);
	if (cub->show_minimap)
		display_map(cub);
	while (i > 0)
	{
		raycasting(cub, angle, i);
		angle += step;
		i--;
	}
	if (cub->show_minimap)
		cpy_img_to_frame_buffer(cub->frame_buffer, *cub->minimap, 0, 0);
}
