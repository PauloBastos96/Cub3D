/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:40:14 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/27 15:02:21 by ffilipe-         ###   ########.fr       */
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

void render_map_block(t_cub *cub, float y, float x, int color)
{
	int i;
	int j;

	i = 0;
	while(i < 10)
	{
		j = 0;
		while(j < 10)
		{
			mlx_pixel_put(cub->mlx,cub->win, x * 10 + j, y * 10 + i, color);
			j++;
		}
		i++;
	}
}

void display_prop(t_image *minimap, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < 10)
	{
		j = 0;
		while(j < 10)
		{
			set_pixel_color(minimap, 10 * x + j, 10 * y + i, color);
			j++;
		}
		i++;
	}
}

void display_map(t_cub *cub)
{
	t_image *minimap;
	
	int y;
	int x;

	minimap = ft_calloc(1, sizeof(t_image));
	minimap->img = mlx_new_image(cub->mlx, cub->width * 10, cub->height * 10);
	y = 0;
	x = 0;
	while(cub->map[y])
	{
		x = 0;
		while(cub->map[y][x])
		{
			if(cub->map[y][x] == '1')
				display_prop(minimap, x, y, 0xffffff);
			if(cub->map[y][x] == '0')
				display_prop(minimap, x, y, 0x000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, minimap->img, 0, 0);
}

///Render a frame to the screen
/// @param cub The cub struct
int	render_frame(t_cub *cub)
{
	static uint64_t	last_update = 0;

	last_update += delta_time();
	if (last_update < 1000 / MAX_FPS)
		return (0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame_buffer->img, 0, 0);
	if (cub->show_fps)
	{
		display_fps(cub, last_update);
		display_map(cub);
	}
	last_update = 0;
	return (0);
}
