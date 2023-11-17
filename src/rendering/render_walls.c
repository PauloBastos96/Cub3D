/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:05:35 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 21:57:55 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/// Select the image to render
/// @param cub The cub struct
/// @param _angle The angle of the ray
/// @param is_vert Is the ray checking for vertical walls
/// @return The image to render
static t_image	*select_image(t_cub *cub, float _angle, bool is_vert)
{
	float	angle;

	angle = rad_to_deg(_angle);
	if (cub->map[cub->prop_y][cub->prop_x] == 'D')
		return (cub->textures->door);
	else if (cub->map[cub->prop_y][cub->prop_x] == '2')
		return (cub->textures->animated_walls[cub->textures->anim_frame]);
	else if (angle >= 0 && angle < 180 && !is_vert)
		return (cub->textures->north);
	else if (angle >= 90 && angle < 270 && is_vert)
		return (cub->textures->west);
	else if (angle >= 180 && angle < 360 && !is_vert)
		return (cub->textures->south);
	else
		return (cub->textures->east);
}

/// Get the y coordinate of the pixel to render
static int	get_y_coord(int iter, int d_start, int d_end)
{
	return (((iter - d_start) * (MAP_SCALE - 1)) / (d_end - d_start));
}

/// Get the color of the pixel to render
/// @param cub The cub struct
/// @param ray A struct containing the distance and angle of the ray
/// @param y The y coordinate of the pixel
/// @return The color of the pixel
static int	set_color(t_cub *cub, t_ray ray, int y)
{
	t_rgb	fog_color;
	float	fog_multi;
	int		color;

	color = get_pixel_color(*select_image(cub, ray.angle, ray.is_vert),
			ray.x_pos, y);
	if (cub->show_fog)
	{
		fog_multi = 1;
		if (ray.distance > 250)
			fog_multi = 3;
		if (ray.distance > 800)
			fog_multi = 4;
		fog_color = int_to_rgb(color);
		fog_color.r = clamp((fog_color.r - fog_multi * (ray.distance
						/ MAP_SCALE)), 0, 255);
		fog_color.g = clamp((fog_color.g - fog_multi * (ray.distance
						/ MAP_SCALE)), 0, 255);
		fog_color.b = clamp((fog_color.b - fog_multi * (ray.distance
						/ MAP_SCALE)), 0, 255);
		color = rgb_to_int(&fog_color);
	}
	return (color);
}

/// Set the limits of the wall to render
/// @param cub The cub struct
/// @param d_start The start of the wall
/// @param d_end The end of the wall
/// @param ray A struct containing the distance and angle of the ray
static void	calculate_limits(t_cub *cub, int *d_start, int *d_end, t_ray ray)
{
	float	p_plane;
	float	fixed_dist;
	int		p_height;

	p_plane = (WINDOW_WIDTH / 2) / tanf(deg_to_rad(FOV / 2));
	fixed_dist = ray.distance * cosf(cub->player->angle - ray.angle);
	p_height = (MAP_SCALE / fixed_dist) * p_plane;
	*d_start = (-p_height / 2) + (WINDOW_HEIGHT / 2);
	*d_end = (p_height / 2) + (WINDOW_HEIGHT / 2);
}

/// Render the walls
/// @param cub The cub struct
/// @param ray A struct containing the distance and angle of the ray
/// @param i The pixel column
/// @param x 
/// @param is_vert Is the ray checking for vertical walls
void	draw_walls(t_cub *cub, t_ray ray, int i)
{
	int			d_start;
	int			d_end;
	int			y;
	int			iter;
	int			max;

	calculate_limits(cub, &d_start, &d_end, ray);
	iter = d_start;
	if (iter < 0)
		iter = 0;
	max = d_end;
	if (max >= WINDOW_HEIGHT)
		max = WINDOW_HEIGHT - 1;
	while (iter <= max)
	{
		y = get_y_coord(iter, d_start, d_end);
		set_pixel_color(cub->frame_buffer, i, iter,
			set_color(cub, ray, y));
		iter++;
	}
}
