/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:03 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/07 12:54:46 by paulorod         ###   ########.fr       */
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
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			set_pixel_color(minimap, MINIMAP_SCALE * x + j,
				MINIMAP_SCALE * y + i, color);
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
void	display_player(t_cub *cub, int color)
{
	float	i;
	float	j;

	i = -0.5 * MINIMAP_SCALE;
	while (i < MINIMAP_SCALE / 2)
	{
		j = -0.5 * MINIMAP_SCALE;
		while (j < MINIMAP_SCALE / 2)
		{
			set_pixel_color(cub->minimap, MINIMAP_SCALE * cub->player->pos_x + j,
				MINIMAP_SCALE * cub->player->pos_y + i, color);
			j++;
		}
		i++;
	}
}

/// Display the minimap on the screen
/// @param cub The cub struct
void	display_map(t_cub *cub)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1')
				display_prop(cub->minimap, x, y, 0xffffff);
			else
				display_prop(cub->minimap, x, y, 0x000000);
			x++;
		}
		y++;
	}
	display_player(cub, 0xffff00);
}
