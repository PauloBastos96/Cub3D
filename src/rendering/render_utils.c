/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:39:11 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/26 14:03:50 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

///Get time of day in miliseconds
/// @return Time of day in miliseconds
uint64_t	gettimeofday_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

///Get time since last update
/// @return Time since last update
uint64_t	delta_time(void)
{
	static uint64_t	last_update = 0;
	uint64_t		current_time;
	uint64_t		delta;

	current_time = gettimeofday_ms();
	if (last_update == 0)
		last_update = current_time - 1;
	delta = current_time - last_update;
	last_update = current_time;
	return (delta);
}

///Get the color of the pixel in position 'x,y'
/// @param img The image to get the pixel color from
/// @param x The x position of the pixel
/// @param y The y position of the pixel
/// @return The color of the pixel in position 'x,y'
uint32_t	get_pixel_color(t_image img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len)
			+ (x * img.bpp / 8))));
}

///Set the color of pixel in position 'x,y', ignoring transparent pixels
/// @param img The image to set the pixel color
/// @param x The x position of the pixel
/// @param y The y position of the pixel
/// @param color The color to set the pixel to
void	set_pixel_color(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img->w && y < img->h)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

///Copy image to the frame buffer
/// @param dst The frame buffer
/// @param src The image to be copied
/// @param x The x position to copy the image to
/// @param y The y position to copy the image to
void	cpy_img_to_frame_buffer(t_image *dst, t_image src, int x, int y)
{
	int			i;
	int			j;
	uint32_t	color;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			color = get_pixel_color(src, i, j);
			set_pixel_color(dst, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
