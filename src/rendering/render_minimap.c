/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:03 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/27 16:40:14 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void display_prop(t_image *minimap, int x, int y, int color)
{
	float i;
	float j;

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

void display_player(t_image *minimap, float x, float y, int color)
{
    float i;
    float j;

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
	minimap->addr = mlx_get_data_addr(minimap->img,
			&(minimap->bpp),
			&(minimap->line_len),
			&(minimap->endian));
	minimap->w = cub->width * 10;
	minimap->h = cub->height * 10;
	
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
    display_player(minimap, cub->player->pos_x, cub->player->pos_y, 0xffff00);
	mlx_put_image_to_window(cub->mlx, cub->win, minimap->img, 0, 0);
}