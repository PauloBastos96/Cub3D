/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:40:14 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/07 12:52:53 by paulorod         ###   ########.fr       */
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

///Render a frame to the screen
/// @param cub The cub struct
int	render_frame(t_cub *cub)
{
	static uint64_t	last_update = 0;

	last_update += delta_time();
	if (last_update < 1000 / MAX_FPS)
		return (0);
	raycast_in_fov(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame_buffer->img, 0, 0);
	if (cub->show_fps)
		display_fps(cub, last_update);
	last_update = 0;
	return (0);
}
