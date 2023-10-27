/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:03 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/27 18:35:08 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Fill a square on the minimap
/// @param minimap The minimap image
/// @param x The x position of the square
/// @param y The y position of the square
/// @param color The color of the square
void	display_prop(t_image *minimap, int x, int y, int color)
{
	float	i;
	float	j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			set_pixel_color(minimap, 10 * x + j, 10 * y + i, color);
			j++;
		}
		i++;
	}
}

/// Display the player on the minimap
/// @param minimap The minimap image
/// @param x The player x position
/// @param y The player y position
/// @param color The color of the player
void	display_player(t_image *minimap, float x, float y, int color)
{
	float	i;
	float	j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			set_pixel_color(minimap, 10 * x + j, 10 * y + i, color);
			j++;
		}
		i++;
	}
}

/// Display the minimap on the screen
/// @param cub The cub struct
void	display_map(t_cub *cub)
{
	t_image	*minimap;
	int		y;
	int		x;

	minimap = create_new_image(cub->mlx, cub->width * 10, cub->height * 10);
	y = 0;
	x = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1')
				display_prop(minimap, x, y, 0xffffff);
			if (cub->map[y][x] == '0')
				display_prop(minimap, x, y, 0x000000);
			x++;
		}
		y++;
	}
	display_player(minimap, cub->player->pos_x, cub->player->pos_y, 0xffff00);
	cpy_img_to_frame_buffer(cub->frame_buffer, *minimap, 0, 0);
	mlx_destroy_image(cub->mlx, minimap->img);
	free(minimap);
}
