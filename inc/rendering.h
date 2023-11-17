/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:55:44 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 16:00:59 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "structs.h"
# include <stdint.h>

int			render_frame(t_cub *cub);
void		cpy_img_to_frame_buffer(t_image *dst, t_image src, int x, int y);
void		set_pixel_color(t_image *img, int x, int y, int color);
void		display_map(t_cub *cub);
void		display_debug_line(t_cub *cub);
void		draw_walls(t_cub *cub, t_ray ray, int i);
void		draw_ray_from_player(t_cub *cub, float x, float y, float angle);
uint32_t	get_pixel_color(t_image img, int x, int y);
t_image		*create_new_image(void *mlx, int width, int height);

#endif
