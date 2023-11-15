/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:40:14 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/15 13:34:58 by paulorod         ###   ########.fr       */
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
	if (cub->show_minimap)
		display_map(cub);
	raycast_in_fov(cub);
	display_debug_line(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame_buffer->img, 0, 0);
	if (cub->show_fps)
		display_fps(cub, last_update);
	last_update = 0;
	return (0);
}
