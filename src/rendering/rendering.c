/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:40:14 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/13 18:44:34 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

///Display FPS on screen
/// @details The fps string is limited to double digits to avoid constant
///			 heap allocations, so the max fps is 99
/// @param cub The cub struct
/// @param delta Time since last update
void	display_fps(t_cub *cub, uint64_t delta)
{
	int			fps;
	char		fps_s[3];

	if (delta == 0)
		delta = 1;
	fps = 1000 / delta;
	fps_s[0] = (fps / 10) + '0';
	fps_s[1] = (fps % 10) + '0';
	fps_s[2] = '\0';
	mlx_string_put(cub->mlx, cub->win, WINDOW_WIDTH - 20, 20, 0xffffff, fps_s);
}

///Display a vertical debug pixel line on screen
void	display_debug_line(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		set_pixel_color(cub->frame_buffer, cub->debug_line, i, 0xffffff);
		i++;
	}
}

/// Render the ceiling or the floor
/// @param cub The cub struct
/// @param is_ceiling Render the ceiling if true, the floor if false
/// @param color The color to render
void	render_half_screen(t_cub *cub, bool is_ceiling, t_rgb *color)
{
	int	i;
	int	j;
	int	limit;

	if (is_ceiling)
	{
		i = 0;
		limit = WINDOW_HEIGHT / 2;
	}
	else
	{
		i = WINDOW_HEIGHT / 2;
		limit = WINDOW_HEIGHT;
	}
	while (i < limit)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			set_pixel_color(cub->frame_buffer,
				j, i, rgb_to_int(color));
			j++;
		}
		i++;
	}
}

t_image	*select_image(t_cub *cub, float _angle, bool is_vert)
{
	float	angle;

	angle = rad_to_deg(_angle);
	if (angle >= 0 && angle < 180 && !is_vert)
		return (cub->textures->north);
	else if (angle >= 90 && angle < 270 && is_vert)
		return (cub->textures->west);
	else if (angle >= 180 && angle < 360 && !is_vert)
		return (cub->textures->south);
	else
		return (cub->textures->east);
}

/*
	y = (0 + (tmp - d_start) * (127 - 0) / (d_end - d_start)))
*/
int	get_y_coord(int iter, int d_start, int d_end)
{
	return (((iter - d_start) * 127) / (d_end - d_start));
}

/// Render the walls
/// @param cub The cub struct
/// @param dist The distance from the player to the wall
/// @param angle The angle of the ray
/// @param i The pixel column
/// @param color [FOR TESTING ONLY] The color to render
void	draw_walls(t_cub *cub, float dist, float angle, int i, int x, bool is_vert)
{
	float	p_plane;
	float	fixed_dist;
	int		p_height;
	int		d_start;
	int		d_end;
	int		color;
	int		y;
	int		iter;
	int		max;

	p_plane = (WINDOW_WIDTH / 2) / tanf(deg_to_rad(FOV / 2));
	fixed_dist = dist * cosf(cub->player->angle - angle);
	p_height = (MAP_SCALE / fixed_dist) * p_plane;
	d_start = (-p_height / 2) + (WINDOW_HEIGHT / 2);
	d_end = (p_height / 2) + (WINDOW_HEIGHT / 2);
	// if (d_start < 0)
	// 	d_start = 0;
	// if (d_end >= WINDOW_HEIGHT)
	// 	d_end = WINDOW_HEIGHT - 1;
	iter = d_start;
	if (iter < 0)
		iter = 0;
	max = d_end;
	if (max >= WINDOW_HEIGHT)
		max = WINDOW_HEIGHT - 1;
	while (iter <= max)
	{
		y = get_y_coord(iter, d_start, d_end);
		if (cub->debug_line == i)
			printf("iter: %d	d_end: %d	y: %d		p_height: %d\n", iter, d_end, y, p_height);
		color = get_pixel_color(*select_image(cub, angle, is_vert), x, y);
		set_pixel_color(cub->frame_buffer, i, iter, color);
		iter++;
	}
}

///Render a frame to the screen
/// @param cub The cub struct
int	render_frame(t_cub *cub)
{
	static uint64_t	last_update = 0;

	last_update += delta_time();
	if (last_update < 1000 / MAX_FPS)
		return (0);
	render_half_screen(cub, true, cub->ceiling_color);
	render_half_screen(cub, false, cub->floor_color);
	raycast_in_fov(cub);
	display_debug_line(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame_buffer->img, 0, 0);
	if (cub->show_fps)
		display_fps(cub, last_update);
	last_update = 0;
	return (0);
}
